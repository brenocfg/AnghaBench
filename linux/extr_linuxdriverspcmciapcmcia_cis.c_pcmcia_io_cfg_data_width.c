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
 unsigned int CISTPL_IO_16BIT ; 
 unsigned int CISTPL_IO_8BIT ; 
 int IO_DATA_PATH_WIDTH_16 ; 
 int IO_DATA_PATH_WIDTH_8 ; 
 int IO_DATA_PATH_WIDTH_AUTO ; 

__attribute__((used)) static int pcmcia_io_cfg_data_width(unsigned int flags)
{
	if (!(flags & CISTPL_IO_8BIT))
		return IO_DATA_PATH_WIDTH_16;
	if (!(flags & CISTPL_IO_16BIT))
		return IO_DATA_PATH_WIDTH_8;
	return IO_DATA_PATH_WIDTH_AUTO;
}