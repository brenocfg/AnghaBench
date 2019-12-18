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
typedef  scalar_t__ sdlRestrictionIntPtr ;

/* Variables and functions */
 int /*<<< orphan*/  efree (scalar_t__) ; 

void delete_restriction_var_int(sdlRestrictionIntPtr ptr)
{
	if (ptr) {
		efree(ptr);
	}
}