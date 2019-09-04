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
struct fusb300 {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB300_CSR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUSB300_CSR_LEN_MSK ; 
 scalar_t__ FUSB300_OFFSET_CSR ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fusb300_set_cxlen(struct fusb300 *fusb300, u32 length)
{
	u32 reg;

	reg = ioread32(fusb300->reg + FUSB300_OFFSET_CSR);
	reg &= ~FUSB300_CSR_LEN_MSK;
	reg |= FUSB300_CSR_LEN(length);
	iowrite32(reg, fusb300->reg + FUSB300_OFFSET_CSR);
}