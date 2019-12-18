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
struct rsc {int dummy; } ;
struct ct_mixer {int /*<<< orphan*/ * amixers; } ;
typedef  enum MIXER_PORT_T { ____Placeholder_MIXER_PORT_T } MIXER_PORT_T ;
typedef  enum CT_AMIXER_CTL { ____Placeholder_CT_AMIXER_CTL } CT_AMIXER_CTL ;

/* Variables and functions */
 int CHN_NUM ; 
 int NUM_CT_AMIXERS ; 
 int get_recording_amixer (int) ; 
 int /*<<< orphan*/  mixer_set_input_port (int /*<<< orphan*/ ,struct rsc*) ; 
 int port_to_amixer (int) ; 

__attribute__((used)) static int mixer_set_input_left(struct ct_mixer *mixer,
				enum MIXER_PORT_T type, struct rsc *rsc)
{
	enum CT_AMIXER_CTL amix = port_to_amixer(type);

	mixer_set_input_port(mixer->amixers[amix*CHN_NUM], rsc);
	amix = get_recording_amixer(amix);
	if (amix < NUM_CT_AMIXERS)
		mixer_set_input_port(mixer->amixers[amix*CHN_NUM], rsc);

	return 0;
}