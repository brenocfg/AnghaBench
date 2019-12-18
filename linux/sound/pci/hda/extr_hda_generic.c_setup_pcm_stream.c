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
struct hda_pcm_stream {scalar_t__ maxbps; scalar_t__ formats; scalar_t__ rates; scalar_t__ channels_max; scalar_t__ channels_min; scalar_t__ substreams; scalar_t__ nid; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */

__attribute__((used)) static void setup_pcm_stream(struct hda_pcm_stream *str,
			     const struct hda_pcm_stream *default_str,
			     const struct hda_pcm_stream *spec_str,
			     hda_nid_t nid)
{
	*str = *default_str;
	if (nid)
		str->nid = nid;
	if (spec_str) {
		if (spec_str->substreams)
			str->substreams = spec_str->substreams;
		if (spec_str->channels_min)
			str->channels_min = spec_str->channels_min;
		if (spec_str->channels_max)
			str->channels_max = spec_str->channels_max;
		if (spec_str->rates)
			str->rates = spec_str->rates;
		if (spec_str->formats)
			str->formats = spec_str->formats;
		if (spec_str->maxbps)
			str->maxbps = spec_str->maxbps;
	}
}