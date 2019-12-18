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
typedef  size_t u32 ;
struct img_spdif_in {int /*<<< orphan*/ * aclkgen_regs; } ;

/* Variables and functions */
 scalar_t__ IMG_SPDIF_IN_ACLKGEN_START ; 
 int /*<<< orphan*/  img_spdif_in_writel (struct img_spdif_in*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void img_spdif_in_aclkgen_writel(struct img_spdif_in *spdif,
						u32 index)
{
	img_spdif_in_writel(spdif, spdif->aclkgen_regs[index],
			IMG_SPDIF_IN_ACLKGEN_START + (index * 0x4));
}