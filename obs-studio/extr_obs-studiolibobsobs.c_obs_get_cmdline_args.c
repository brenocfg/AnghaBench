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
struct obs_cmdline_args {int dummy; } ;

/* Variables and functions */
 struct obs_cmdline_args cmdline_args ; 

struct obs_cmdline_args obs_get_cmdline_args(void)
{
	return cmdline_args;
}