#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct samsung_i2s_priv {int quirks; scalar_t__ addr; TYPE_1__* variant_regs; } ;
struct i2s_dai {TYPE_2__* pdev; struct samsung_i2s_priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int bfs_off; int bfs_mask; } ;

/* Variables and functions */
 int EXYNOS5420_MOD_BCLK_128FS ; 
 int EXYNOS5420_MOD_BCLK_192FS ; 
 int EXYNOS5420_MOD_BCLK_256FS ; 
 int EXYNOS5420_MOD_BCLK_64FS ; 
 int EXYNOS5420_MOD_BCLK_96FS ; 
 scalar_t__ I2SMOD ; 
 int MOD_BCLK_16FS ; 
 int MOD_BCLK_24FS ; 
 int MOD_BCLK_32FS ; 
 int MOD_BCLK_48FS ; 
 int QUIRK_SUPPORTS_TDM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void set_bfs(struct i2s_dai *i2s, unsigned bfs)
{
	struct samsung_i2s_priv *priv = i2s->priv;
	u32 mod = readl(priv->addr + I2SMOD);
	int tdm = priv->quirks & QUIRK_SUPPORTS_TDM;
	int bfs_shift = priv->variant_regs->bfs_off;

	/* Non-TDM I2S controllers do not support BCLK > 48 * FS */
	if (!tdm && bfs > 48) {
		dev_err(&i2s->pdev->dev, "Unsupported BCLK divider\n");
		return;
	}

	mod &= ~(priv->variant_regs->bfs_mask << bfs_shift);

	switch (bfs) {
	case 48:
		mod |= (MOD_BCLK_48FS << bfs_shift);
		break;
	case 32:
		mod |= (MOD_BCLK_32FS << bfs_shift);
		break;
	case 24:
		mod |= (MOD_BCLK_24FS << bfs_shift);
		break;
	case 16:
		mod |= (MOD_BCLK_16FS << bfs_shift);
		break;
	case 64:
		mod |= (EXYNOS5420_MOD_BCLK_64FS << bfs_shift);
		break;
	case 96:
		mod |= (EXYNOS5420_MOD_BCLK_96FS << bfs_shift);
		break;
	case 128:
		mod |= (EXYNOS5420_MOD_BCLK_128FS << bfs_shift);
		break;
	case 192:
		mod |= (EXYNOS5420_MOD_BCLK_192FS << bfs_shift);
		break;
	case 256:
		mod |= (EXYNOS5420_MOD_BCLK_256FS << bfs_shift);
		break;
	default:
		dev_err(&i2s->pdev->dev, "Wrong BCLK Divider!\n");
		return;
	}

	writel(mod, priv->addr + I2SMOD);
}