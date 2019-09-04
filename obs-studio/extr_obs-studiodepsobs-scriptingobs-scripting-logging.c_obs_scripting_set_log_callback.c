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
typedef  int /*<<< orphan*/  scripting_log_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  callback ; 
 void* param ; 

void obs_scripting_set_log_callback(scripting_log_handler_t handler,
		void *log_param)
{
	callback = handler;
	param = log_param;
}