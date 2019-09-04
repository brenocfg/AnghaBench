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
struct tegra20_ac97 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA20_AC97_FIFO1_SCR ; 
 int /*<<< orphan*/  TEGRA20_AC97_FIFO_SCR_REC_FULL_EN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tegra20_ac97_stop_capture(struct tegra20_ac97 *ac97)
{
	regmap_update_bits(ac97->regmap, TEGRA20_AC97_FIFO1_SCR,
			   TEGRA20_AC97_FIFO_SCR_REC_FULL_EN, 0);
}