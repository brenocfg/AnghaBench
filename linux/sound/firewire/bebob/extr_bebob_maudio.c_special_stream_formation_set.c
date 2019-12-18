#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct special_params {size_t dig_in_fmt; size_t dig_out_fmt; int /*<<< orphan*/  is1814; } ;
struct snd_bebob {TYPE_4__* rx_stream_formations; TYPE_3__* tx_stream_formations; struct special_params* maudio_special_quirk; } ;
struct TYPE_8__ {unsigned int pcm; int midi; } ;
struct TYPE_7__ {unsigned int pcm; int midi; } ;
struct TYPE_6__ {int member_0; int member_1; int member_2; } ;
struct TYPE_5__ {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 size_t AMDTP_IN_STREAM ; 
 size_t AMDTP_OUT_STREAM ; 
 int SND_BEBOB_STRM_FMT_ENTRIES ; 

__attribute__((used)) static void
special_stream_formation_set(struct snd_bebob *bebob)
{
	static const unsigned int ch_table[2][2][3] = {
		/* AMDTP_OUT_STREAM */
		{ {  6,  6,  4 },	/* SPDIF */
		  { 12,  8,  4 } },	/* ADAT */
		/* AMDTP_IN_STREAM */
		{ { 10, 10,  2 },	/* SPDIF */
		  { 16, 12,  2 } }	/* ADAT */
	};
	struct special_params *params = bebob->maudio_special_quirk;
	unsigned int i, max;

	max = SND_BEBOB_STRM_FMT_ENTRIES - 1;
	if (!params->is1814)
		max -= 2;

	for (i = 0; i < max; i++) {
		bebob->tx_stream_formations[i + 1].pcm =
			ch_table[AMDTP_IN_STREAM][params->dig_in_fmt][i / 2];
		bebob->tx_stream_formations[i + 1].midi = 1;

		bebob->rx_stream_formations[i + 1].pcm =
			ch_table[AMDTP_OUT_STREAM][params->dig_out_fmt][i / 2];
		bebob->rx_stream_formations[i + 1].midi = 1;
	}
}