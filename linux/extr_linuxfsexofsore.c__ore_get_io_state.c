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
struct osd_sg_entry {int dummy; } ;
struct ore_per_dev_state {int dummy; } ;
struct ore_layout {int dummy; } ;
struct ore_io_state {int extra_part_alloc; unsigned int max_par_pages; unsigned int sgs_per_dev; struct ore_components* oc; struct ore_layout* layout; TYPE_1__* per_dev; void* parity_pages; } ;
struct ore_components {int dummy; } ;
struct TYPE_2__ {struct osd_sg_entry* sglist; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INT_MAX ; 
 int /*<<< orphan*/  ORE_DBGMSG (char*,...) ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (struct ore_io_state*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 size_t max (int,int) ; 
 scalar_t__ unlikely (int) ; 

int  _ore_get_io_state(struct ore_layout *layout,
			struct ore_components *oc, unsigned numdevs,
			unsigned sgs_per_dev, unsigned num_par_pages,
			struct ore_io_state **pios)
{
	struct ore_io_state *ios;
	size_t size_ios, size_extra, size_total;
	void *ios_extra;

	/*
	 * The desired layout looks like this, with the extra_allocation
	 * items pointed at from fields within ios or per_dev:

	struct __alloc_all_io_state {
		struct ore_io_state ios;
		struct ore_per_dev_state per_dev[numdevs];
		union {
			struct osd_sg_entry sglist[sgs_per_dev * numdevs];
			struct page *pages[num_par_pages];
		} extra_allocation;
	} whole_allocation;

	*/

	/* This should never happen, so abort early if it ever does. */
	if (sgs_per_dev && num_par_pages) {
		ORE_DBGMSG("Tried to use both pages and sglist\n");
		*pios = NULL;
		return -EINVAL;
	}

	if (numdevs > (INT_MAX - sizeof(*ios)) /
		       sizeof(struct ore_per_dev_state))
		return -ENOMEM;
	size_ios = sizeof(*ios) + sizeof(struct ore_per_dev_state) * numdevs;

	if (sgs_per_dev * numdevs > INT_MAX / sizeof(struct osd_sg_entry))
		return -ENOMEM;
	if (num_par_pages > INT_MAX / sizeof(struct page *))
		return -ENOMEM;
	size_extra = max(sizeof(struct osd_sg_entry) * (sgs_per_dev * numdevs),
			 sizeof(struct page *) * num_par_pages);

	size_total = size_ios + size_extra;

	if (likely(size_total <= PAGE_SIZE)) {
		ios = kzalloc(size_total, GFP_KERNEL);
		if (unlikely(!ios)) {
			ORE_DBGMSG("Failed kzalloc bytes=%zd\n", size_total);
			*pios = NULL;
			return -ENOMEM;
		}
		ios_extra = (char *)ios + size_ios;
	} else {
		ios = kzalloc(size_ios, GFP_KERNEL);
		if (unlikely(!ios)) {
			ORE_DBGMSG("Failed alloc first part bytes=%zd\n",
				   size_ios);
			*pios = NULL;
			return -ENOMEM;
		}
		ios_extra = kzalloc(size_extra, GFP_KERNEL);
		if (unlikely(!ios_extra)) {
			ORE_DBGMSG("Failed alloc second part bytes=%zd\n",
				   size_extra);
			kfree(ios);
			*pios = NULL;
			return -ENOMEM;
		}

		/* In this case the per_dev[0].sgilist holds the pointer to
		 * be freed
		 */
		ios->extra_part_alloc = true;
	}

	if (num_par_pages) {
		ios->parity_pages = ios_extra;
		ios->max_par_pages = num_par_pages;
	}
	if (sgs_per_dev) {
		struct osd_sg_entry *sgilist = ios_extra;
		unsigned d;

		for (d = 0; d < numdevs; ++d) {
			ios->per_dev[d].sglist = sgilist;
			sgilist += sgs_per_dev;
		}
		ios->sgs_per_dev = sgs_per_dev;
	}

	ios->layout = layout;
	ios->oc = oc;
	*pios = ios;
	return 0;
}