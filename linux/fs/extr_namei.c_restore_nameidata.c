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
struct nameidata {scalar_t__ stack; scalar_t__ internal; int /*<<< orphan*/  total_link_count; struct nameidata* saved; } ;
struct TYPE_2__ {struct nameidata* nameidata; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static void restore_nameidata(void)
{
	struct nameidata *now = current->nameidata, *old = now->saved;

	current->nameidata = old;
	if (old)
		old->total_link_count = now->total_link_count;
	if (now->stack != now->internal)
		kfree(now->stack);
}