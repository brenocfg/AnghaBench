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
typedef  int u8 ;
struct mtpav {int inmidistate; int /*<<< orphan*/  inmidiport; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_mtpav_inmidi_process (struct mtpav*,int) ; 
 int /*<<< orphan*/  translate_hwport_to_subdevice (struct mtpav*,int) ; 

__attribute__((used)) static void snd_mtpav_inmidi_h(struct mtpav *mcrd, u8 inbyte)
{
	if (inbyte >= 0xf8) {
		/* real-time midi code */
		snd_mtpav_inmidi_process(mcrd, inbyte);
		return;
	}

	if (mcrd->inmidistate == 0) {	// awaiting command
		if (inbyte == 0xf5)	// MTP port #
			mcrd->inmidistate = 1;
		else
			snd_mtpav_inmidi_process(mcrd, inbyte);
	} else if (mcrd->inmidistate) {
		mcrd->inmidiport = translate_hwport_to_subdevice(mcrd, inbyte);
		mcrd->inmidistate = 0;
	}
}