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
struct artpec6_pcie {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void artpec6_pcie_writel(struct artpec6_pcie *artpec6_pcie, u32 offset, u32 val)
{
	regmap_write(artpec6_pcie->regmap, offset, val);
}