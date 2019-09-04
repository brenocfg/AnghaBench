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
struct TYPE_2__ {int /*<<< orphan*/  pdm; int /*<<< orphan*/  pcm; } ;
struct sdw_intel {TYPE_1__ cdns; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pdi_stream_ch_update (struct sdw_intel*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int intel_pdi_ch_update(struct sdw_intel *sdw)
{
	/* First update PCM streams followed by PDM streams */
	intel_pdi_stream_ch_update(sdw, &sdw->cdns.pcm, true);
	intel_pdi_stream_ch_update(sdw, &sdw->cdns.pdm, false);

	return 0;
}