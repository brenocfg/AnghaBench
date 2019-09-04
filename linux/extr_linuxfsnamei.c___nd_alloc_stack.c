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
struct saved {int dummy; } ;
struct nameidata {int flags; struct saved* stack; int /*<<< orphan*/  internal; } ;

/* Variables and functions */
 int ECHILD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LOOKUP_RCU ; 
 int /*<<< orphan*/  MAXSYMLINKS ; 
 struct saved* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct saved*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __nd_alloc_stack(struct nameidata *nd)
{
	struct saved *p;

	if (nd->flags & LOOKUP_RCU) {
		p= kmalloc_array(MAXSYMLINKS, sizeof(struct saved),
				  GFP_ATOMIC);
		if (unlikely(!p))
			return -ECHILD;
	} else {
		p= kmalloc_array(MAXSYMLINKS, sizeof(struct saved),
				  GFP_KERNEL);
		if (unlikely(!p))
			return -ENOMEM;
	}
	memcpy(p, nd->internal, sizeof(nd->internal));
	nd->stack = p;
	return 0;
}