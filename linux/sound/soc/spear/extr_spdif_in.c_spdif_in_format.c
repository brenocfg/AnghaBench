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
typedef  int u32 ;
struct spdif_in_dev {scalar_t__ io_base; } ;

/* Variables and functions */
#define  SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE 129 
#define  SNDRV_PCM_FORMAT_S16_LE 128 
 scalar_t__ SPDIF_IN_CTRL ; 
 int SPDIF_XTRACT_16BIT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void spdif_in_format(struct spdif_in_dev *host, u32 format)
{
	u32 ctrl = readl(host->io_base + SPDIF_IN_CTRL);

	switch (format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		ctrl |= SPDIF_XTRACT_16BIT;
		break;

	case SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE:
		ctrl &= ~SPDIF_XTRACT_16BIT;
		break;
	}

	writel(ctrl, host->io_base + SPDIF_IN_CTRL);
}