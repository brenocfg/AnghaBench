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
struct rocker_desc_info {TYPE_1__* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  comp_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCKER_DMA_DESC_COMP_ERR_GEN ; 

__attribute__((used)) static void rocker_desc_gen_clear(const struct rocker_desc_info *desc_info)
{
	desc_info->desc->comp_err &= ~ROCKER_DMA_DESC_COMP_ERR_GEN;
}