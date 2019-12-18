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
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 scalar_t__ IsUnderPostmaster ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addin_request_allowed ; 
 int /*<<< orphan*/  total_addin_request ; 

void
RequestAddinShmemSpace(Size size)
{
	if (IsUnderPostmaster || !addin_request_allowed)
		return;					/* too late */
	total_addin_request = add_size(total_addin_request, size);
}