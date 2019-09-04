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
struct scatterlist {unsigned int length; scalar_t__ offset; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct scatterlist* kmalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,unsigned int const) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 

__attribute__((used)) static struct scatterlist *wa_xfer_create_subset_sg(struct scatterlist *in_sg,
	const unsigned int bytes_transferred,
	const unsigned int bytes_to_transfer, int *out_num_sgs)
{
	struct scatterlist *out_sg;
	unsigned int bytes_processed = 0, offset_into_current_page_data = 0,
		nents;
	struct scatterlist *current_xfer_sg = in_sg;
	struct scatterlist *current_seg_sg, *last_seg_sg;

	/* skip previously transferred pages. */
	while ((current_xfer_sg) &&
			(bytes_processed < bytes_transferred)) {
		bytes_processed += current_xfer_sg->length;

		/* advance the sg if current segment starts on or past the
			next page. */
		if (bytes_processed <= bytes_transferred)
			current_xfer_sg = sg_next(current_xfer_sg);
	}

	/* the data for the current segment starts in current_xfer_sg.
		calculate the offset. */
	if (bytes_processed > bytes_transferred) {
		offset_into_current_page_data = current_xfer_sg->length -
			(bytes_processed - bytes_transferred);
	}

	/* calculate the number of pages needed by this segment. */
	nents = DIV_ROUND_UP((bytes_to_transfer +
		offset_into_current_page_data +
		current_xfer_sg->offset),
		PAGE_SIZE);

	out_sg = kmalloc((sizeof(struct scatterlist) * nents), GFP_ATOMIC);
	if (out_sg) {
		sg_init_table(out_sg, nents);

		/* copy the portion of the incoming SG that correlates to the
		 * data to be transferred by this segment to the segment SG. */
		last_seg_sg = current_seg_sg = out_sg;
		bytes_processed = 0;

		/* reset nents and calculate the actual number of sg entries
			needed. */
		nents = 0;
		while ((bytes_processed < bytes_to_transfer) &&
				current_seg_sg && current_xfer_sg) {
			unsigned int page_len = min((current_xfer_sg->length -
				offset_into_current_page_data),
				(bytes_to_transfer - bytes_processed));

			sg_set_page(current_seg_sg, sg_page(current_xfer_sg),
				page_len,
				current_xfer_sg->offset +
				offset_into_current_page_data);

			bytes_processed += page_len;

			last_seg_sg = current_seg_sg;
			current_seg_sg = sg_next(current_seg_sg);
			current_xfer_sg = sg_next(current_xfer_sg);

			/* only the first page may require additional offset. */
			offset_into_current_page_data = 0;
			nents++;
		}

		/* update num_sgs and terminate the list since we may have
		 *  concatenated pages. */
		sg_mark_end(last_seg_sg);
		*out_num_sgs = nents;
	}

	return out_sg;
}