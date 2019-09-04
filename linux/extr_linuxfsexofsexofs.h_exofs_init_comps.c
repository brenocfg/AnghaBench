#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ore_components {int numdevs; int /*<<< orphan*/ * ods; struct ore_comp* comps; int /*<<< orphan*/  single_comp; int /*<<< orphan*/  first_dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; int /*<<< orphan*/  partition; } ;
struct ore_comp {TYPE_5__ obj; int /*<<< orphan*/  cred; } ;
struct TYPE_9__ {unsigned int numdevs; int /*<<< orphan*/ * ods; } ;
struct TYPE_8__ {int group_width; int mirrors_p1; int group_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  partition; } ;
struct TYPE_7__ {TYPE_1__ obj; } ;
struct exofs_sb_info {TYPE_4__ oc; TYPE_3__ layout; TYPE_2__ one_comp; } ;
typedef  int /*<<< orphan*/  osd_id ;

/* Variables and functions */
 int /*<<< orphan*/  EC_SINGLE_COMP ; 
 int /*<<< orphan*/  exofs_make_credential (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static inline void exofs_init_comps(struct ore_components *oc,
				    struct ore_comp *one_comp,
				    struct exofs_sb_info *sbi, osd_id oid)
{
	unsigned dev_mod = (unsigned)oid, first_dev;

	one_comp->obj.partition = sbi->one_comp.obj.partition;
	one_comp->obj.id = oid;
	exofs_make_credential(one_comp->cred, &one_comp->obj);

	oc->first_dev = 0;
	oc->numdevs = sbi->layout.group_width * sbi->layout.mirrors_p1 *
							sbi->layout.group_count;
	oc->single_comp = EC_SINGLE_COMP;
	oc->comps = one_comp;

	/* Round robin device view of the table */
	first_dev = (dev_mod * sbi->layout.mirrors_p1) % sbi->oc.numdevs;
	oc->ods = &sbi->oc.ods[first_dev];
}