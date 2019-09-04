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
struct ore_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** ods; } ;
struct exofs_sb_info {TYPE_1__ oc; } ;
struct exofs_dev {int /*<<< orphan*/  ored; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXOFS_ERR (char*,unsigned int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ ** kzalloc (size_t const,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __alloc_dev_table(struct exofs_sb_info *sbi, unsigned numdevs,
		      struct exofs_dev **peds)
{
	/* Twice bigger table: See exofs_init_comps() and comment at
	 * exofs_read_lookup_dev_table()
	 */
	const size_t numores = numdevs * 2 - 1;
	struct exofs_dev *eds;
	unsigned i;

	sbi->oc.ods = kzalloc(numores * sizeof(struct ore_dev *) +
			      numdevs * sizeof(struct exofs_dev), GFP_KERNEL);
	if (unlikely(!sbi->oc.ods)) {
		EXOFS_ERR("ERROR: failed allocating Device array[%d]\n",
			  numdevs);
		return -ENOMEM;
	}

	/* Start of allocated struct exofs_dev entries */
	*peds = eds = (void *)sbi->oc.ods[numores];
	/* Initialize pointers into struct exofs_dev */
	for (i = 0; i < numdevs; ++i)
		sbi->oc.ods[i] = &eds[i].ored;
	return 0;
}