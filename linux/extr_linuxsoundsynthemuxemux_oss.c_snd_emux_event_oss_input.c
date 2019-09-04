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
struct TYPE_3__ {unsigned char* d; } ;
struct TYPE_4__ {TYPE_1__ raw8; } ;
struct snd_seq_event {scalar_t__ type; TYPE_2__ data; } ;
struct snd_emux_port {struct snd_emux* emu; } ;
struct snd_emux {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_SEQ_EVENT_OSS ; 
 unsigned char _EMUX_OSS_MODE_FLAG ; 
 unsigned char _EMUX_OSS_MODE_VALUE_MASK ; 
 int /*<<< orphan*/  emuspec_control (struct snd_emux*,struct snd_emux_port*,unsigned char,unsigned char*,int,int) ; 
 int /*<<< orphan*/  gusspec_control (struct snd_emux*,struct snd_emux_port*,unsigned char,unsigned char*,int,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_emux_event_input (struct snd_seq_event*,int,void*,int,int) ; 

__attribute__((used)) static int
snd_emux_event_oss_input(struct snd_seq_event *ev, int direct, void *private_data,
			 int atomic, int hop)
{
	struct snd_emux *emu;
	struct snd_emux_port *p;
	unsigned char cmd, *data;

	p = private_data;
	if (snd_BUG_ON(!p))
		return -EINVAL;
	emu = p->emu;
	if (snd_BUG_ON(!emu))
		return -EINVAL;
	if (ev->type != SNDRV_SEQ_EVENT_OSS)
		return snd_emux_event_input(ev, direct, private_data, atomic, hop);

	data = ev->data.raw8.d;
	/* only SEQ_PRIVATE is accepted */
	if (data[0] != 0xfe)
		return 0;
	cmd = data[2] & _EMUX_OSS_MODE_VALUE_MASK;
	if (data[2] & _EMUX_OSS_MODE_FLAG)
		emuspec_control(emu, p, cmd, data, atomic, hop);
	else
		gusspec_control(emu, p, cmd, data, atomic, hop);
	return 0;
}