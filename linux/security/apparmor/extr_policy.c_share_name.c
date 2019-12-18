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
struct TYPE_3__ {int /*<<< orphan*/  hname; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  hname; } ;
struct aa_profile {TYPE_1__ label; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_get_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void share_name(struct aa_profile *old, struct aa_profile *new)
{
	aa_put_str(new->base.hname);
	aa_get_str(old->base.hname);
	new->base.hname = old->base.hname;
	new->base.name = old->base.name;
	new->label.hname = old->label.hname;
}