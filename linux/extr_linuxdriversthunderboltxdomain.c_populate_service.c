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
struct tb_service {int /*<<< orphan*/  key; int /*<<< orphan*/  prtcstns; int /*<<< orphan*/  prtcrevs; int /*<<< orphan*/  prtcvers; int /*<<< orphan*/  prtcid; } ;
struct tb_property_dir {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  immediate; struct tb_property_dir* dir; } ;
struct tb_property {int /*<<< orphan*/  key; TYPE_1__ value; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TB_PROPERTY_TYPE_VALUE ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tb_property* tb_property_find (struct tb_property_dir*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int populate_service(struct tb_service *svc,
			    struct tb_property *property)
{
	struct tb_property_dir *dir = property->value.dir;
	struct tb_property *p;

	/* Fill in standard properties */
	p = tb_property_find(dir, "prtcid", TB_PROPERTY_TYPE_VALUE);
	if (p)
		svc->prtcid = p->value.immediate;
	p = tb_property_find(dir, "prtcvers", TB_PROPERTY_TYPE_VALUE);
	if (p)
		svc->prtcvers = p->value.immediate;
	p = tb_property_find(dir, "prtcrevs", TB_PROPERTY_TYPE_VALUE);
	if (p)
		svc->prtcrevs = p->value.immediate;
	p = tb_property_find(dir, "prtcstns", TB_PROPERTY_TYPE_VALUE);
	if (p)
		svc->prtcstns = p->value.immediate;

	svc->key = kstrdup(property->key, GFP_KERNEL);
	if (!svc->key)
		return -ENOMEM;

	return 0;
}