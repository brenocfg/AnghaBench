#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct osd_dev {int dummy; } ;
struct TYPE_3__ {unsigned int numdevs; struct exofs_sb_info* ods; } ;
struct exofs_sb_info {TYPE_1__ oc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct exofs_sb_info*) ; 
 struct osd_dev* ore_comp_dev (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  ore_comp_set_dev (TYPE_1__*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osduld_put_device (struct osd_dev*) ; 

__attribute__((used)) static void exofs_free_sbi(struct exofs_sb_info *sbi)
{
	unsigned numdevs = sbi->oc.numdevs;

	while (numdevs) {
		unsigned i = --numdevs;
		struct osd_dev *od = ore_comp_dev(&sbi->oc, i);

		if (od) {
			ore_comp_set_dev(&sbi->oc, i, NULL);
			osduld_put_device(od);
		}
	}
	kfree(sbi->oc.ods);
	kfree(sbi);
}