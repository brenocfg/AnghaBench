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
struct xlgmac_pdata {int /*<<< orphan*/  hw_ops; int /*<<< orphan*/  desc_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  xlgmac_init_desc_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xlgmac_init_hw_ops (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xlgmac_init_all_ops(struct xlgmac_pdata *pdata)
{
	xlgmac_init_desc_ops(&pdata->desc_ops);
	xlgmac_init_hw_ops(&pdata->hw_ops);
}