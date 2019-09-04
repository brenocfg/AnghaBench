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
struct knav_dma_desc {int /*<<< orphan*/ * sw_data; } ;

/* Variables and functions */

__attribute__((used)) static u32 get_sw_data(int index, struct knav_dma_desc *desc)
{
	/* No Endian conversion needed as this data is untouched by hw */
	return desc->sw_data[index];
}