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
 int /*<<< orphan*/  HPI_VOLUME_AUTOFADE ; 
 scalar_t__ hpi_control_query (scalar_t__ const,int /*<<< orphan*/ ,scalar_t__ const,int /*<<< orphan*/ ,scalar_t__*) ; 

u16 hpi_volume_query_auto_fade_profile(const u32 h_volume, const u32 i,
	u16 *profile)
{
	u16 e;
	u32 u;
	e = hpi_control_query(h_volume, HPI_VOLUME_AUTOFADE, i, 0, &u);
	*profile = (u16)u;
	return e;
}