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
struct nameidata {scalar_t__ depth; scalar_t__ stack; scalar_t__ internal; } ;

/* Variables and functions */
 scalar_t__ EMBEDDED_LEVELS ; 
 int __nd_alloc_stack (struct nameidata*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline int nd_alloc_stack(struct nameidata *nd)
{
	if (likely(nd->depth != EMBEDDED_LEVELS))
		return 0;
	if (likely(nd->stack != nd->internal))
		return 0;
	return __nd_alloc_stack(nd);
}