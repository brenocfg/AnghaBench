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
struct sg_splitter {int nents; struct sg_splitter* out_sg; } ;
struct scatterlist {int nents; struct scatterlist* out_sg; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct sg_splitter* kcalloc (int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sg_splitter*) ; 
 struct sg_splitter* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int sg_calculate_split (struct sg_splitter*,int const,int const,int /*<<< orphan*/  const,size_t const*,struct sg_splitter*,int) ; 
 int const sg_nents (struct sg_splitter*) ; 
 int /*<<< orphan*/  sg_split_mapped (struct sg_splitter*,int const) ; 
 int /*<<< orphan*/  sg_split_phys (struct sg_splitter*,int const) ; 

int sg_split(struct scatterlist *in, const int in_mapped_nents,
	     const off_t skip, const int nb_splits,
	     const size_t *split_sizes,
	     struct scatterlist **out, int *out_mapped_nents,
	     gfp_t gfp_mask)
{
	int i, ret;
	struct sg_splitter *splitters;

	splitters = kcalloc(nb_splits, sizeof(*splitters), gfp_mask);
	if (!splitters)
		return -ENOMEM;

	ret = sg_calculate_split(in, sg_nents(in), nb_splits, skip, split_sizes,
			   splitters, false);
	if (ret < 0)
		goto err;

	ret = -ENOMEM;
	for (i = 0; i < nb_splits; i++) {
		splitters[i].out_sg = kmalloc_array(splitters[i].nents,
						    sizeof(struct scatterlist),
						    gfp_mask);
		if (!splitters[i].out_sg)
			goto err;
	}

	/*
	 * The order of these 3 calls is important and should be kept.
	 */
	sg_split_phys(splitters, nb_splits);
	if (in_mapped_nents) {
		ret = sg_calculate_split(in, in_mapped_nents, nb_splits, skip,
					 split_sizes, splitters, true);
		if (ret < 0)
			goto err;
		sg_split_mapped(splitters, nb_splits);
	}

	for (i = 0; i < nb_splits; i++) {
		out[i] = splitters[i].out_sg;
		if (out_mapped_nents)
			out_mapped_nents[i] = splitters[i].nents;
	}

	kfree(splitters);
	return 0;

err:
	for (i = 0; i < nb_splits; i++)
		kfree(splitters[i].out_sg);
	kfree(splitters);
	return ret;
}