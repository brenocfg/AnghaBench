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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; scalar_t__ private_data; } ;
struct TYPE_5__ {int* item; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct clk_cache {int count; TYPE_1__* s; } ;
struct snd_card_asihpi {struct clk_cache cc; } ;
struct TYPE_4__ {scalar_t__ source; scalar_t__ index; } ;

/* Variables and functions */
 scalar_t__ HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT ; 
 scalar_t__ hpi_sample_clock_get_source (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ hpi_sample_clock_get_source_index (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int snd_asihpi_clksrc_get(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_card_asihpi *asihpi =
			(struct snd_card_asihpi *)(kcontrol->private_data);
	struct clk_cache *clkcache = &asihpi->cc;
	u32 h_control = kcontrol->private_value;
	u16 source, srcindex = 0;
	int i;

	ucontrol->value.enumerated.item[0] = 0;
	if (hpi_sample_clock_get_source(h_control, &source))
		source = 0;

	if (source == HPI_SAMPLECLOCK_SOURCE_AESEBU_INPUT)
		if (hpi_sample_clock_get_source_index(h_control, &srcindex))
			srcindex = 0;

	for (i = 0; i < clkcache->count; i++)
		if ((clkcache->s[i].source == source) &&
			(clkcache->s[i].index == srcindex))
			break;

	ucontrol->value.enumerated.item[0] = i;

	return 0;
}