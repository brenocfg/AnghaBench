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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct sclp_sd_data {size_t esize_bytes; size_t dsize_bytes; void* data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  SD_EQ_HALT ; 
 int /*<<< orphan*/  SD_EQ_SIZE ; 
 int /*<<< orphan*/  SD_EQ_STORE_DATA ; 
 unsigned long __get_free_page (int) ; 
 int /*<<< orphan*/  array_size (size_t,size_t) ; 
 unsigned long base_asce_alloc (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  base_asce_free (unsigned long) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int sclp_sd_sync (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sclp_sd_store_data(struct sclp_sd_data *result, u8 di)
{
	u32 dsize = 0, esize = 0;
	unsigned long page, asce = 0;
	void *data = NULL;
	int rc;

	page = __get_free_page(GFP_KERNEL | GFP_DMA);
	if (!page)
		return -ENOMEM;

	/* Get size */
	rc = sclp_sd_sync(page, SD_EQ_SIZE, di, 0, 0, &dsize, &esize);
	if (rc)
		goto out;
	if (dsize == 0)
		goto out_result;

	/* Allocate memory */
	data = vzalloc(array_size((size_t)dsize, PAGE_SIZE));
	if (!data) {
		rc = -ENOMEM;
		goto out;
	}

	/* Get translation table for buffer */
	asce = base_asce_alloc((unsigned long) data, dsize);
	if (!asce) {
		vfree(data);
		rc = -ENOMEM;
		goto out;
	}

	/* Get data */
	rc = sclp_sd_sync(page, SD_EQ_STORE_DATA, di, asce, (u64) data, &dsize,
			  &esize);
	if (rc) {
		/* Cancel running request if interrupted */
		if (rc == -ERESTARTSYS)
			sclp_sd_sync(page, SD_EQ_HALT, di, 0, 0, NULL, NULL);
		vfree(data);
		goto out;
	}

out_result:
	result->esize_bytes = (size_t) esize * PAGE_SIZE;
	result->dsize_bytes = (size_t) dsize * PAGE_SIZE;
	result->data = data;

out:
	base_asce_free(asce);
	free_page(page);

	return rc;
}