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
struct parport {int dummy; } ;
struct TYPE_2__ {int par_dt_reg; } ;

/* Variables and functions */
 unsigned char PARPORT_STATUS_BUSY ; 
 unsigned char PARPORT_STATUS_ERROR ; 
 unsigned char PARPORT_STATUS_SELECT ; 
 TYPE_1__ st_mfp ; 

__attribute__((used)) static unsigned char
parport_atari_read_status(struct parport *p)
{
	return ((st_mfp.par_dt_reg & 1 ? 0 : PARPORT_STATUS_BUSY) |
		PARPORT_STATUS_SELECT | PARPORT_STATUS_ERROR);
}