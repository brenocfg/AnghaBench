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
struct os_inhibit_info {int dummy; } ;
typedef  int /*<<< orphan*/  os_inhibit_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (char const*) ; 
 int /*<<< orphan*/ * bzalloc (int) ; 

os_inhibit_t *os_inhibit_sleep_create(const char *reason)
{
	UNUSED_PARAMETER(reason);
	return bzalloc(sizeof(struct os_inhibit_info));
}