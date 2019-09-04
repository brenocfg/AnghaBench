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
typedef  size_t u8 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __par_io_config_pin (int /*<<< orphan*/ *,size_t,int,int,int,int) ; 
 size_t num_par_io_ports ; 
 int /*<<< orphan*/ * par_io ; 

int par_io_config_pin(u8 port, u8 pin, int dir, int open_drain,
		      int assignment, int has_irq)
{
	if (!par_io || port >= num_par_io_ports)
		return -EINVAL;

	__par_io_config_pin(&par_io[port], pin, dir, open_drain, assignment,
			    has_irq);
	return 0;
}