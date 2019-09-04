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
struct filename {scalar_t__ refcnt; scalar_t__ name; scalar_t__ iname; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __putname (struct filename*) ; 
 int /*<<< orphan*/  kfree (struct filename*) ; 

void putname(struct filename *name)
{
	BUG_ON(name->refcnt <= 0);

	if (--name->refcnt > 0)
		return;

	if (name->name != name->iname) {
		__putname(name->name);
		kfree(name);
	} else
		__putname(name);
}