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
struct omap_mcbsp {scalar_t__ max_tx_thres; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCBSP_WRITE (struct omap_mcbsp*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  THRSH2 ; 

__attribute__((used)) static void omap_mcbsp_set_tx_threshold(struct omap_mcbsp *mcbsp, u16 threshold)
{
	if (threshold && threshold <= mcbsp->max_tx_thres)
		MCBSP_WRITE(mcbsp, THRSH2, threshold - 1);
}