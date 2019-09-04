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
typedef  unsigned int u32 ;
struct tegra_vde {scalar_t__ mbe; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDE_WR (unsigned int,scalar_t__) ; 
 int tegra_vde_wait_mbe (struct tegra_vde*) ; 

__attribute__((used)) static int tegra_vde_setup_mbe_frame_idx(struct tegra_vde *vde,
					 unsigned int refs_nb,
					 bool setup_refs)
{
	u32 frame_idx_enb_mask = 0;
	u32 value;
	unsigned int frame_idx;
	unsigned int idx;
	int err;

	VDE_WR(0xD0000000 | (0 << 23), vde->mbe + 0x80);
	VDE_WR(0xD0200000 | (0 << 23), vde->mbe + 0x80);

	err = tegra_vde_wait_mbe(vde);
	if (err)
		return err;

	if (!setup_refs)
		return 0;

	for (idx = 0, frame_idx = 1; idx < refs_nb; idx++, frame_idx++) {
		VDE_WR(0xD0000000 | (frame_idx << 23), vde->mbe + 0x80);
		VDE_WR(0xD0200000 | (frame_idx << 23), vde->mbe + 0x80);

		frame_idx_enb_mask |= frame_idx << (6 * (idx % 4));

		if (idx % 4 == 3 || idx == refs_nb - 1) {
			value = 0xC0000000;
			value |= (idx >> 2) << 24;
			value |= frame_idx_enb_mask;

			VDE_WR(value, vde->mbe + 0x80);

			err = tegra_vde_wait_mbe(vde);
			if (err)
				return err;

			frame_idx_enb_mask = 0;
		}
	}

	return 0;
}