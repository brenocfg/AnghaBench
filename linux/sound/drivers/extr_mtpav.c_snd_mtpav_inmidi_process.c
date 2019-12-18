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
typedef  int /*<<< orphan*/  u8 ;
struct mtpav_port {int mode; int /*<<< orphan*/  input; } ;
struct mtpav {size_t inmidiport; int num_ports; struct mtpav_port* ports; } ;

/* Variables and functions */
 int MTPAV_MODE_INPUT_TRIGGERED ; 
 int MTPAV_PIDX_BROADCAST ; 
 int /*<<< orphan*/  snd_rawmidi_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void snd_mtpav_inmidi_process(struct mtpav *mcrd, u8 inbyte)
{
	struct mtpav_port *portp;

	if ((int)mcrd->inmidiport > mcrd->num_ports * 2 + MTPAV_PIDX_BROADCAST)
		return;

	portp = &mcrd->ports[mcrd->inmidiport];
	if (portp->mode & MTPAV_MODE_INPUT_TRIGGERED)
		snd_rawmidi_receive(portp->input, &inbyte, 1);
}