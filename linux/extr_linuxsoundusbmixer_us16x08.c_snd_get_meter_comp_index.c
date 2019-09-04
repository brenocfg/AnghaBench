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
struct snd_us16x08_meter_store {int comp_active_index; int comp_index; TYPE_1__* comp_store; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** val; } ;

/* Variables and functions */
 size_t COMP_STORE_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_US16X08_ID_COMP_SWITCH ; 
 size_t SND_US16X08_MAX_CHANNELS ; 

__attribute__((used)) static int snd_get_meter_comp_index(struct snd_us16x08_meter_store *store)
{
	int ret;

	/* any channel active */
	if (store->comp_active_index) {
		/* check for stereo link */
		if (store->comp_active_index & 0x20) {
			/* reset comp_index to left channel*/
			if (store->comp_index -
				store->comp_active_index > 1)
				store->comp_index =
				store->comp_active_index;

			ret = store->comp_index++ & 0x1F;
		} else {
			/* no stereo link */
			ret = store->comp_active_index;
		}
	} else {
		/* skip channels with no compressor active */
		while (!store->comp_store->val[
			COMP_STORE_IDX(SND_US16X08_ID_COMP_SWITCH)]
			[store->comp_index - 1]
			&& store->comp_index <= SND_US16X08_MAX_CHANNELS) {
			store->comp_index++;
		}
		ret = store->comp_index++;
		if (store->comp_index > SND_US16X08_MAX_CHANNELS)
			store->comp_index = 1;
	}
	return ret;
}