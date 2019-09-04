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

/* Variables and functions */
 scalar_t__ is_vmalloc_addr (void*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,char*) ; 

void
ip_set_free(void *members)
{
	pr_debug("%p: free with %s\n", members,
		 is_vmalloc_addr(members) ? "vfree" : "kfree");
	kvfree(members);
}