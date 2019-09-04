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
struct osd_dev {int dummy; } ;
struct ore_io_state {TYPE_1__* oc; } ;
struct TYPE_2__ {int /*<<< orphan*/  ods; int /*<<< orphan*/  numdevs; int /*<<< orphan*/  first_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ORE_DBGMSG2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct osd_dev* ore_comp_dev (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static struct osd_dev *_ios_od(struct ore_io_state *ios, unsigned index)
{
	ORE_DBGMSG2("oc->first_dev=%d oc->numdevs=%d i=%d oc->ods=%p\n",
		    ios->oc->first_dev, ios->oc->numdevs, index,
		    ios->oc->ods);

	return ore_comp_dev(ios->oc, index);
}