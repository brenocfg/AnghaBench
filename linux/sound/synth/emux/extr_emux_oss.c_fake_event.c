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
struct TYPE_4__ {int channel; int param; int value; } ;
struct TYPE_3__ {TYPE_2__ control; } ;
struct snd_seq_event {TYPE_1__ data; int /*<<< orphan*/  type; } ;
struct snd_emux_port {int dummy; } ;
struct snd_emux {int dummy; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_CONTROLLER ; 
 int /*<<< orphan*/  memset (struct snd_seq_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_emux_event_input (struct snd_seq_event*,int /*<<< orphan*/ ,struct snd_emux_port*,int,int) ; 

__attribute__((used)) static void
fake_event(struct snd_emux *emu, struct snd_emux_port *port, int ch, int param, int val, int atomic, int hop)
{
	struct snd_seq_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.type = SNDRV_SEQ_EVENT_CONTROLLER;
	ev.data.control.channel = ch;
	ev.data.control.param = param;
	ev.data.control.value = val;
	snd_emux_event_input(&ev, 0, port, atomic, hop);
}