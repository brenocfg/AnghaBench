#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 unsigned int EROFS_PERCPU_NR_PAGES ; 
 unsigned int PAGE_SIZE ; 
 TYPE_1__* erofs_pcpubuf ; 
 void* erofs_vmap (struct page**,unsigned int) ; 
 int /*<<< orphan*/  erofs_vunmap (void*,unsigned int) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 size_t smp_processor_id () ; 
 int z_erofs_unzip_lz4 (void*,void*,unsigned int,unsigned int) ; 

int z_erofs_vle_unzip_fast_percpu(struct page **compressed_pages,
				  unsigned clusterpages,
				  struct page **pages,
				  unsigned outlen,
				  unsigned short pageofs)
{
	void *vin, *vout;
	unsigned nr_pages, i, j;
	int ret;

	if (outlen + pageofs > EROFS_PERCPU_NR_PAGES * PAGE_SIZE)
		return -ENOTSUPP;

	nr_pages = DIV_ROUND_UP(outlen + pageofs, PAGE_SIZE);

	if (clusterpages == 1) {
		vin = kmap_atomic(compressed_pages[0]);
	} else {
		vin = erofs_vmap(compressed_pages, clusterpages);
		if (!vin)
			return -ENOMEM;
	}

	preempt_disable();
	vout = erofs_pcpubuf[smp_processor_id()].data;

	ret = z_erofs_unzip_lz4(vin, vout + pageofs,
		clusterpages * PAGE_SIZE, outlen);

	if (ret < 0)
		goto out;
	ret = 0;

	for (i = 0; i < nr_pages; ++i) {
		j = min((unsigned)PAGE_SIZE - pageofs, outlen);

		if (pages[i] != NULL) {
			if (clusterpages == 1 &&
			    pages[i] == compressed_pages[0]) {
				memcpy(vin + pageofs, vout + pageofs, j);
			} else {
				void *dst = kmap_atomic(pages[i]);

				memcpy(dst + pageofs, vout + pageofs, j);
				kunmap_atomic(dst);
			}
		}
		vout += PAGE_SIZE;
		outlen -= j;
		pageofs = 0;
	}

out:
	preempt_enable();

	if (clusterpages == 1)
		kunmap_atomic(vin);
	else
		erofs_vunmap(vin, clusterpages);

	return ret;
}