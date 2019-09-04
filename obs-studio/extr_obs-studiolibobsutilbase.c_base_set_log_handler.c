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
typedef  scalar_t__ log_handler_t ;

/* Variables and functions */
 scalar_t__ def_log_handler ; 
 scalar_t__ log_handler ; 
 void* log_param ; 

void base_set_log_handler(log_handler_t handler, void *param)
{
	if (!handler)
		handler = def_log_handler;

	log_param   = param;
	log_handler = handler;
}