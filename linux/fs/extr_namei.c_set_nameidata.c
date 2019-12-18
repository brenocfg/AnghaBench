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
struct nameidata {int dfd; struct nameidata* saved; int /*<<< orphan*/  total_link_count; struct filename* name; int /*<<< orphan*/  internal; int /*<<< orphan*/  stack; } ;
struct filename {int dummy; } ;
struct TYPE_2__ {struct nameidata* nameidata; } ;

/* Variables and functions */
 TYPE_1__* current ; 

__attribute__((used)) static void set_nameidata(struct nameidata *p, int dfd, struct filename *name)
{
	struct nameidata *old = current->nameidata;
	p->stack = p->internal;
	p->dfd = dfd;
	p->name = name;
	p->total_link_count = old ? old->total_link_count : 0;
	p->saved = old;
	current->nameidata = p;
}