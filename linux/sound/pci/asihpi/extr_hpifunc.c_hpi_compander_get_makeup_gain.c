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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_COMPANDER_MAKEUPGAIN ; 
 int /*<<< orphan*/  hpi_control_log_get2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,short*,int /*<<< orphan*/ *) ; 

u16 hpi_compander_get_makeup_gain(u32 h_control, short *makeup_gain0_01dB)
{
	return hpi_control_log_get2(h_control, HPI_COMPANDER_MAKEUPGAIN,
		makeup_gain0_01dB, NULL);
}