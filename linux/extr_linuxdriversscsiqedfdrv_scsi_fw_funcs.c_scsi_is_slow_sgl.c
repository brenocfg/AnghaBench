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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ SCSI_NUM_SGES_SLOW_SGL_THR ; 

bool scsi_is_slow_sgl(u16 num_sges, bool small_mid_sge)
{
	return (num_sges > SCSI_NUM_SGES_SLOW_SGL_THR && small_mid_sge);
}