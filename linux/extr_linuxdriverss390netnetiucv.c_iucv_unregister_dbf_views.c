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
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_dbf_data ; 
 int /*<<< orphan*/  iucv_dbf_setup ; 
 int /*<<< orphan*/  iucv_dbf_trace ; 

__attribute__((used)) static void iucv_unregister_dbf_views(void)
{
	debug_unregister(iucv_dbf_setup);
	debug_unregister(iucv_dbf_data);
	debug_unregister(iucv_dbf_trace);
}