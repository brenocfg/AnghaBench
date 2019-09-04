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
struct geni_wrapper {scalar_t__ base; } ;
struct geni_se {struct geni_wrapper* wrapper; } ;

/* Variables and functions */
 scalar_t__ QUP_HW_VER_REG ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

u32 geni_se_get_qup_hw_version(struct geni_se *se)
{
	struct geni_wrapper *wrapper = se->wrapper;

	return readl_relaxed(wrapper->base + QUP_HW_VER_REG);
}