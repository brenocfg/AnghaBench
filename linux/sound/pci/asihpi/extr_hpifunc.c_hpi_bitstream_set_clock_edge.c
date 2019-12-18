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
 int /*<<< orphan*/  HPI_BITSTREAM_CLOCK_EDGE ; 
 int /*<<< orphan*/  hpi_control_param_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 hpi_bitstream_set_clock_edge(u32 h_control, u16 edge_type)
{
	return hpi_control_param_set(h_control, HPI_BITSTREAM_CLOCK_EDGE,
		edge_type, 0);
}