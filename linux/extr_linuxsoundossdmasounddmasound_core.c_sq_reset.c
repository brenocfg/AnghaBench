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
 scalar_t__ shared_resources_initialised ; 
 int /*<<< orphan*/  sq_reset_output () ; 

__attribute__((used)) static void sq_reset(void)
{
	sq_reset_output() ;
	/* we could consider resetting the shared_resources_owner here... but I
	   think it is probably still rather non-obvious to application writer
	*/

	/* we release everything else though */
	shared_resources_initialised = 0 ;
}