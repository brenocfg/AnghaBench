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
 unsigned int PAGE_SIZE ; 
 TYPE_1__* erofs_pcpubuf ; 
 void* erofs_vmap (struct page**,unsigned int) ; 
 int /*<<< orphan*/  erofs_vunmap (void*,unsigned int) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 size_t smp_processor_id () ; 
 int z_erofs_unzip_lz4 (void*,void*,unsigned int,unsigned int) ; 

int z_erofs_vle_unzip_vmap(struct page **compressed_pages,
			   unsigned clusterpages,
			   void *vout,
			   unsigned llen,
			   unsigned short pageofs,
			   bool overlapped)
{
	void *vin;
	unsigned i;
	int ret;

	if (overlapped) {
		preempt_disable();
		vin = erofs_pcpubuf[smp_processor_id()].data;

		for (i = 0; i < clusterpages; ++i) {
			void *t = kmap_atomic(compressed_pages[i]);

			memcpy(vin + PAGE_SIZE *i, t, PAGE_SIZE);
			kunmap_atomic(t);
		}
	} else if (clusterpages == 1)
		vin = kmap_atomic(compressed_pages[0]);
	else {
		vin = erofs_vmap(compressed_pages, clusterpages);
	}

	ret = z_erofs_unzip_lz4(vin, vout + pageofs,
		clusterpages * PAGE_SIZE, llen);
	if (ret > 0)
		ret = 0;

	if (!overlapped) {
		if (clusterpages == 1)
			kunmap_atomic(vin);
		else {
			erofs_vunmap(vin, clusterpages);
		}
	} else
		preempt_enable();

	return ret;
}