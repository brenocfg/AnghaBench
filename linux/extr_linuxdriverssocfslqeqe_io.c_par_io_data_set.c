#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  cpdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int QE_PIO_PINS ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int num_par_io_ports ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* par_io ; 

int par_io_data_set(u8 port, u8 pin, u8 val)
{
	u32 pin_mask, tmp_val;

	if (port >= num_par_io_ports)
		return -EINVAL;
	if (pin >= QE_PIO_PINS)
		return -EINVAL;
	/* calculate pin location */
	pin_mask = (u32) (1 << (QE_PIO_PINS - 1 - pin));

	tmp_val = in_be32(&par_io[port].cpdata);

	if (val == 0)		/* clear */
		out_be32(&par_io[port].cpdata, ~pin_mask & tmp_val);
	else			/* set */
		out_be32(&par_io[port].cpdata, pin_mask | tmp_val);

	return 0;
}