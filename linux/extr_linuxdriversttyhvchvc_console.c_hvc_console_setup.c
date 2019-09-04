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
struct console {size_t index; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t MAX_NR_HVC_CONSOLES ; 
 int* vtermnos ; 

__attribute__((used)) static int hvc_console_setup(struct console *co, char *options)
{	
	if (co->index < 0 || co->index >= MAX_NR_HVC_CONSOLES)
		return -ENODEV;

	if (vtermnos[co->index] == -1)
		return -ENODEV;

	return 0;
}