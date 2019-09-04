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
struct tegra_vde {scalar_t__ sxe; scalar_t__ bsev; int /*<<< orphan*/  decode_completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDE_WR (int,scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_vde_decode_frame(struct tegra_vde *vde,
				   unsigned int macroblocks_nb)
{
	reinit_completion(&vde->decode_completion);

	VDE_WR(0x00000001, vde->bsev + 0x8C);
	VDE_WR(0x20000000 | (macroblocks_nb - 1), vde->sxe + 0x00);
}