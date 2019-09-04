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
struct dma_desc {int /*<<< orphan*/  des3; } ;

/* Variables and functions */
 int TDES3_OWN ; 
 int TDES3_OWN_SHIFT ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwmac4_get_tx_owner(struct dma_desc *p)
{
	return (le32_to_cpu(p->des3) & TDES3_OWN) >> TDES3_OWN_SHIFT;
}