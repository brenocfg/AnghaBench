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
struct mixer_build {TYPE_1__* mixer; } ;
struct TYPE_2__ {int protocol; } ;

/* Variables and functions */
#define  UAC_VERSION_1 130 
#define  UAC_VERSION_2 129 
#define  UAC_VERSION_3 128 
 int build_audio_procunit (struct mixer_build*,int,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  procunits ; 
 int /*<<< orphan*/  uac3_procunits ; 

__attribute__((used)) static int parse_audio_processing_unit(struct mixer_build *state, int unitid,
				       void *raw_desc)
{
	switch (state->mixer->protocol) {
	case UAC_VERSION_1:
	case UAC_VERSION_2:
	default:
		return build_audio_procunit(state, unitid, raw_desc,
					    procunits, false);
	case UAC_VERSION_3:
		return build_audio_procunit(state, unitid, raw_desc,
					    uac3_procunits, false);
	}
}