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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_4__ {int max; scalar_t__ min; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_info {TYPE_1__ value; int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_MAX_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 scalar_t__ hpi_meter_query_channels (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_asihpi_meter_info(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_info *uinfo)
{
	u32 h_control = kcontrol->private_value;
	u32 count;
	u16 err;
	err = hpi_meter_query_channels(h_control, &count);
	if (err)
		count = HPI_MAX_CHANNELS;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = count;
	uinfo->value.integer.min = 0;
	uinfo->value.integer.max = 0x7FFFFFFF;
	return 0;
}