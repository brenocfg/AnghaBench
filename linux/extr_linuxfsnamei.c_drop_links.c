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
struct saved {int /*<<< orphan*/  done; } ;
struct nameidata {int depth; struct saved* stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_delayed_call (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_delayed_call (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drop_links(struct nameidata *nd)
{
	int i = nd->depth;
	while (i--) {
		struct saved *last = nd->stack + i;
		do_delayed_call(&last->done);
		clear_delayed_call(&last->done);
	}
}