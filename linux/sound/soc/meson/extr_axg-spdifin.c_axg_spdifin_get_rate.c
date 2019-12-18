#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct axg_spdifin {TYPE_1__* conf; int /*<<< orphan*/  map; } ;
struct TYPE_2__ {unsigned int* mode_rates; } ;

/* Variables and functions */
 unsigned int FIELD_GET (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int SPDIFIN_MODE_NUM ; 
 int /*<<< orphan*/  SPDIFIN_STAT0 ; 
 int /*<<< orphan*/  SPDIFIN_STAT0_MAXW ; 
 int /*<<< orphan*/  SPDIFIN_STAT0_MODE ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int axg_spdifin_get_rate(struct axg_spdifin *priv)
{
	unsigned int stat, mode, rate = 0;

	regmap_read(priv->map, SPDIFIN_STAT0, &stat);
	mode = FIELD_GET(SPDIFIN_STAT0_MODE, stat);

	/*
	 * If max width is zero, we are not capturing anything.
	 * Also Sometimes, when the capture is on but there is no data,
	 * mode is SPDIFIN_MODE_NUM, but not always ...
	 */
	if (FIELD_GET(SPDIFIN_STAT0_MAXW, stat) &&
	    mode < SPDIFIN_MODE_NUM)
		rate = priv->conf->mode_rates[mode];

	return rate;
}