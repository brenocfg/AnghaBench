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
struct xa_state {void* xa_node; } ;

/* Variables and functions */
 scalar_t__ xa_is_zero (void*) ; 
 scalar_t__ xas_error (struct xa_state*) ; 

__attribute__((used)) static void *xas_result(struct xa_state *xas, void *curr)
{
	if (xa_is_zero(curr))
		return NULL;
	if (xas_error(xas))
		curr = xas->xa_node;
	return curr;
}