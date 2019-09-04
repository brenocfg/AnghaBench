#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long version; unsigned long last_page; unsigned long nr_badpages; unsigned long* badpages; } ;
struct TYPE_3__ {int /*<<< orphan*/  magic; } ;
union swap_header {TYPE_2__ info; TYPE_1__ magic; } ;
struct swap_info_struct {int lowest_bit; int cluster_next; unsigned long highest_bit; scalar_t__ cluster_nr; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 unsigned long MAX_SWAP_BADPAGES ; 
 int PAGE_SHIFT ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 unsigned long UINT_MAX ; 
 int i_size_read (struct inode*) ; 
 unsigned long max_swapfile_size () ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int swab32 (unsigned long) ; 
 int /*<<< orphan*/  swab32s (unsigned long*) ; 

__attribute__((used)) static unsigned long read_swap_header(struct swap_info_struct *p,
					union swap_header *swap_header,
					struct inode *inode)
{
	int i;
	unsigned long maxpages;
	unsigned long swapfilepages;
	unsigned long last_page;

	if (memcmp("SWAPSPACE2", swap_header->magic.magic, 10)) {
		pr_err("Unable to find swap-space signature\n");
		return 0;
	}

	/* swap partition endianess hack... */
	if (swab32(swap_header->info.version) == 1) {
		swab32s(&swap_header->info.version);
		swab32s(&swap_header->info.last_page);
		swab32s(&swap_header->info.nr_badpages);
		if (swap_header->info.nr_badpages > MAX_SWAP_BADPAGES)
			return 0;
		for (i = 0; i < swap_header->info.nr_badpages; i++)
			swab32s(&swap_header->info.badpages[i]);
	}
	/* Check the swap header's sub-version */
	if (swap_header->info.version != 1) {
		pr_warn("Unable to handle swap header version %d\n",
			swap_header->info.version);
		return 0;
	}

	p->lowest_bit  = 1;
	p->cluster_next = 1;
	p->cluster_nr = 0;

	maxpages = max_swapfile_size();
	last_page = swap_header->info.last_page;
	if (!last_page) {
		pr_warn("Empty swap-file\n");
		return 0;
	}
	if (last_page > maxpages) {
		pr_warn("Truncating oversized swap area, only using %luk out of %luk\n",
			maxpages << (PAGE_SHIFT - 10),
			last_page << (PAGE_SHIFT - 10));
	}
	if (maxpages > last_page) {
		maxpages = last_page + 1;
		/* p->max is an unsigned int: don't overflow it */
		if ((unsigned int)maxpages == 0)
			maxpages = UINT_MAX;
	}
	p->highest_bit = maxpages - 1;

	if (!maxpages)
		return 0;
	swapfilepages = i_size_read(inode) >> PAGE_SHIFT;
	if (swapfilepages && maxpages > swapfilepages) {
		pr_warn("Swap area shorter than signature indicates\n");
		return 0;
	}
	if (swap_header->info.nr_badpages && S_ISREG(inode->i_mode))
		return 0;
	if (swap_header->info.nr_badpages > MAX_SWAP_BADPAGES)
		return 0;

	return maxpages;
}