#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_cmnd {int dummy; } ;
struct scatterlist {unsigned int offset; unsigned int length; } ;
struct page {int dummy; } ;
typedef  enum xfer_buf_dir { ____Placeholder_xfer_buf_dir } xfer_buf_dir ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int TO_XFER_BUF ; 
 unsigned char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int scsi_bufflen (struct scsi_cmnd*) ; 
 unsigned int scsi_sg_count (struct scsi_cmnd*) ; 
 scalar_t__ scsi_sglist (struct scsi_cmnd*) ; 
 struct page* sg_page (struct scatterlist*) ; 

unsigned int rtsx_stor_access_xfer_buf(unsigned char *buffer,
				       unsigned int buflen,
				       struct scsi_cmnd *srb,
				       unsigned int *index,
				       unsigned int *offset,
				       enum xfer_buf_dir dir)
{
	unsigned int cnt;

	/* If not using scatter-gather, just transfer the data directly. */
	if (scsi_sg_count(srb) == 0) {
		unsigned char *sgbuffer;

		if (*offset >= scsi_bufflen(srb))
			return 0;
		cnt = min(buflen, scsi_bufflen(srb) - *offset);

		sgbuffer = (unsigned char *)scsi_sglist(srb) + *offset;

		if (dir == TO_XFER_BUF)
			memcpy(sgbuffer, buffer, cnt);
		else
			memcpy(buffer, sgbuffer, cnt);
		*offset += cnt;

	/*
	 * Using scatter-gather.  We have to go through the list one entry
	 * at a time.  Each s-g entry contains some number of pages, and
	 * each page has to be kmap()'ed separately.
	 */
	} else {
		struct scatterlist *sg =
				(struct scatterlist *)scsi_sglist(srb)
				+ *index;

		/*
		 * This loop handles a single s-g list entry, which may
		 * include multiple pages.  Find the initial page structure
		 * and the starting offset within the page, and update
		 * the *offset and *index values for the next loop.
		 */
		cnt = 0;
		while (cnt < buflen && *index < scsi_sg_count(srb)) {
			struct page *page = sg_page(sg) +
					((sg->offset + *offset) >> PAGE_SHIFT);
			unsigned int poff = (sg->offset + *offset) &
					    (PAGE_SIZE - 1);
			unsigned int sglen = sg->length - *offset;

			if (sglen > buflen - cnt) {
				/* Transfer ends within this s-g entry */
				sglen = buflen - cnt;
				*offset += sglen;
			} else {
				/* Transfer continues to next s-g entry */
				*offset = 0;
				++*index;
				++sg;
			}

			while (sglen > 0) {
				unsigned int plen = min(sglen, (unsigned int)
						PAGE_SIZE - poff);
				unsigned char *ptr = kmap(page);

				if (dir == TO_XFER_BUF)
					memcpy(ptr + poff, buffer + cnt, plen);
				else
					memcpy(buffer + cnt, ptr + poff, plen);
				kunmap(page);

				/* Start at the beginning of the next page */
				poff = 0;
				++page;
				cnt += plen;
				sglen -= plen;
			}
		}
	}

	/* Return the amount actually transferred */
	return cnt;
}