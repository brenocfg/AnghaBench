#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {scalar_t__ private_data; } ;
struct TYPE_5__ {size_t items; size_t item; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_3__ value; int /*<<< orphan*/  type; } ;
struct clk_cache {size_t count; TYPE_1__* s; } ;
struct snd_card_asihpi {struct clk_cache cc; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_asihpi_clksrc_info(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_info *uinfo)
{
	struct snd_card_asihpi *asihpi =
			(struct snd_card_asihpi *)(kcontrol->private_data);
	struct clk_cache *clkcache = &asihpi->cc;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.enumerated.items = clkcache->count;

	if (uinfo->value.enumerated.item >= uinfo->value.enumerated.items)
		uinfo->value.enumerated.item =
				uinfo->value.enumerated.items - 1;

	strcpy(uinfo->value.enumerated.name,
	       clkcache->s[uinfo->value.enumerated.item].name);
	return 0;
}