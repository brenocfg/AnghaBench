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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_CHANNEL_MODE_MODE ; 
 scalar_t__ hpi_control_query (scalar_t__ const,int /*<<< orphan*/ ,scalar_t__ const,int /*<<< orphan*/ ,scalar_t__*) ; 

u16 hpi_channel_mode_query_mode(const u32 h_mode, const u32 index,
	u16 *pw_mode)
{
	u32 qr;
	u16 err;

	err = hpi_control_query(h_mode, HPI_CHANNEL_MODE_MODE, index, 0, &qr);
	*pw_mode = (u16)qr;
	return err;
}