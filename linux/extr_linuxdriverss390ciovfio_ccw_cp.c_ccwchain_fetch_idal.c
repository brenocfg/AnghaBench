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
typedef  unsigned long u64 ;
struct pfn_array_table {scalar_t__ pat_pa; } ;
struct channel_program {int /*<<< orphan*/  mdev; } ;
struct ccwchain {struct pfn_array_table* ch_pat; struct ccw1* ch_ccw; } ;
struct ccw1 {scalar_t__ cda; int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  idaw_iova ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int copy_from_iova (int /*<<< orphan*/ ,unsigned long*,scalar_t__,unsigned int) ; 
 unsigned int idal_nr_words (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 unsigned long* kzalloc (unsigned int,int) ; 
 int pfn_array_alloc_pin (scalar_t__,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  pfn_array_table_idal_create_words (struct pfn_array_table*,unsigned long*) ; 
 int pfn_array_table_init (struct pfn_array_table*,unsigned int) ; 
 int /*<<< orphan*/  pfn_array_table_unpin_free (struct pfn_array_table*,int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (unsigned long*) ; 

__attribute__((used)) static int ccwchain_fetch_idal(struct ccwchain *chain,
			       int idx,
			       struct channel_program *cp)
{
	struct ccw1 *ccw;
	struct pfn_array_table *pat;
	unsigned long *idaws;
	u64 idaw_iova;
	unsigned int idaw_nr, idaw_len;
	int i, ret;

	ccw = chain->ch_ccw + idx;

	if (!ccw->count)
		return 0;

	/* Calculate size of idaws. */
	ret = copy_from_iova(cp->mdev, &idaw_iova, ccw->cda, sizeof(idaw_iova));
	if (ret)
		return ret;
	idaw_nr = idal_nr_words((void *)(idaw_iova), ccw->count);
	idaw_len = idaw_nr * sizeof(*idaws);

	/* Pin data page(s) in memory. */
	pat = chain->ch_pat + idx;
	ret = pfn_array_table_init(pat, idaw_nr);
	if (ret)
		goto out_init;

	/* Translate idal ccw to use new allocated idaws. */
	idaws = kzalloc(idaw_len, GFP_DMA | GFP_KERNEL);
	if (!idaws) {
		ret = -ENOMEM;
		goto out_unpin;
	}

	ret = copy_from_iova(cp->mdev, idaws, ccw->cda, idaw_len);
	if (ret)
		goto out_free_idaws;

	ccw->cda = virt_to_phys(idaws);

	for (i = 0; i < idaw_nr; i++) {
		idaw_iova = *(idaws + i);

		ret = pfn_array_alloc_pin(pat->pat_pa + i, cp->mdev,
					  idaw_iova, 1);
		if (ret < 0)
			goto out_free_idaws;
	}

	pfn_array_table_idal_create_words(pat, idaws);

	return 0;

out_free_idaws:
	kfree(idaws);
out_unpin:
	pfn_array_table_unpin_free(pat, cp->mdev);
out_init:
	ccw->cda = 0;
	return ret;
}