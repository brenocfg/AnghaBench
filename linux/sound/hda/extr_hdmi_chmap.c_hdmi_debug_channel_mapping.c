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
struct TYPE_3__ {int (* pin_get_slot_channel ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;} ;
struct hdac_chmap {TYPE_2__* hdac; TYPE_1__ ops; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdmi_debug_channel_mapping(struct hdac_chmap *chmap,
				       hda_nid_t pin_nid)
{
#ifdef CONFIG_SND_DEBUG_VERBOSE
	int i;
	int channel;

	for (i = 0; i < 8; i++) {
		channel = chmap->ops.pin_get_slot_channel(
				chmap->hdac, pin_nid, i);
		dev_dbg(&chmap->hdac->dev, "HDMI: ASP channel %d => slot %d\n",
						channel, i);
	}
#endif
}