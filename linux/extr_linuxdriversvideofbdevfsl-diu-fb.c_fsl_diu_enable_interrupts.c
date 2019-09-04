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
typedef  int /*<<< orphan*/  u32 ;
struct fsl_diu_data {TYPE_1__* diu_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NOT_COHERENT_CACHE ; 
 int /*<<< orphan*/  INT_UNDRUN ; 
 int /*<<< orphan*/  INT_VSYNC ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clrbits32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fsl_diu_enable_interrupts(struct fsl_diu_data *data)
{
	u32 int_mask = INT_UNDRUN; /* enable underrun detection */

	if (IS_ENABLED(CONFIG_NOT_COHERENT_CACHE))
		int_mask |= INT_VSYNC; /* enable vertical sync */

	clrbits32(&data->diu_reg->int_mask, int_mask);
}