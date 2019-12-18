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
struct pstore_record {int compressed; scalar_t__ type; char* buf; int size; scalar_t__ ecc_notice_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PSTORE_TYPE_DMESG ; 
 int /*<<< orphan*/  big_oops_buf ; 
 int big_oops_buf_sz ; 
 int crypto_comp_decompress (int /*<<< orphan*/ ,char*,int,char*,int*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 char* kmemdup (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  tfm ; 

__attribute__((used)) static void decompress_record(struct pstore_record *record)
{
	int ret;
	int unzipped_len;
	char *unzipped, *workspace;

	if (!record->compressed)
		return;

	/* Only PSTORE_TYPE_DMESG support compression. */
	if (record->type != PSTORE_TYPE_DMESG) {
		pr_warn("ignored compressed record type %d\n", record->type);
		return;
	}

	/* Missing compression buffer means compression was not initialized. */
	if (!big_oops_buf) {
		pr_warn("no decompression method initialized!\n");
		return;
	}

	/* Allocate enough space to hold max decompression and ECC. */
	unzipped_len = big_oops_buf_sz;
	workspace = kmalloc(unzipped_len + record->ecc_notice_size,
			    GFP_KERNEL);
	if (!workspace)
		return;

	/* After decompression "unzipped_len" is almost certainly smaller. */
	ret = crypto_comp_decompress(tfm, record->buf, record->size,
					  workspace, &unzipped_len);
	if (ret) {
		pr_err("crypto_comp_decompress failed, ret = %d!\n", ret);
		kfree(workspace);
		return;
	}

	/* Append ECC notice to decompressed buffer. */
	memcpy(workspace + unzipped_len, record->buf + record->size,
	       record->ecc_notice_size);

	/* Copy decompressed contents into an minimum-sized allocation. */
	unzipped = kmemdup(workspace, unzipped_len + record->ecc_notice_size,
			   GFP_KERNEL);
	kfree(workspace);
	if (!unzipped)
		return;

	/* Swap out compressed contents with decompressed contents. */
	kfree(record->buf);
	record->buf = unzipped;
	record->size = unzipped_len;
	record->compressed = false;
}