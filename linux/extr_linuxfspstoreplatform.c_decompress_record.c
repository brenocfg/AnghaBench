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
struct pstore_record {int compressed; scalar_t__ type; char* buf; int size; int ecc_notice_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PSTORE_TYPE_DMESG ; 
 char* big_oops_buf ; 
 int /*<<< orphan*/  big_oops_buf_sz ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int pstore_decompress (char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decompress_record(struct pstore_record *record)
{
	int unzipped_len;
	char *decompressed;

	if (!record->compressed)
		return;

	/* Only PSTORE_TYPE_DMESG support compression. */
	if (record->type != PSTORE_TYPE_DMESG) {
		pr_warn("ignored compressed record type %d\n", record->type);
		return;
	}

	/* No compression method has created the common buffer. */
	if (!big_oops_buf) {
		pr_warn("no decompression buffer allocated\n");
		return;
	}

	unzipped_len = pstore_decompress(record->buf, big_oops_buf,
					 record->size, big_oops_buf_sz);
	if (unzipped_len <= 0) {
		pr_err("decompression failed: %d\n", unzipped_len);
		return;
	}

	/* Build new buffer for decompressed contents. */
	decompressed = kmalloc(unzipped_len + record->ecc_notice_size,
			       GFP_KERNEL);
	if (!decompressed) {
		pr_err("decompression ran out of memory\n");
		return;
	}
	memcpy(decompressed, big_oops_buf, unzipped_len);

	/* Append ECC notice to decompressed buffer. */
	memcpy(decompressed + unzipped_len, record->buf + record->size,
	       record->ecc_notice_size);

	/* Swap out compresed contents with decompressed contents. */
	kfree(record->buf);
	record->buf = decompressed;
	record->size = unzipped_len;
	record->compressed = false;
}