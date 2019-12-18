#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dsa_handle ;
struct TYPE_5__ {TYPE_1__* control; } ;
typedef  TYPE_2__ dsa_area ;
struct TYPE_4__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DSM_HANDLE_INVALID ; 

dsa_handle
dsa_get_handle(dsa_area *area)
{
	Assert(area->control->handle != DSM_HANDLE_INVALID);
	return area->control->handle;
}