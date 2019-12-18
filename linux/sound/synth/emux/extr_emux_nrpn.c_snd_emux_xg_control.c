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
struct snd_midi_channel {int /*<<< orphan*/ * control; } ;
struct snd_emux_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMUX_FX_FLAG_ADD ; 
 int send_converted_effect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_emux_port*,struct snd_midi_channel*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xg_effects ; 

int
snd_emux_xg_control(struct snd_emux_port *port, struct snd_midi_channel *chan,
		    int param)
{
	return send_converted_effect(xg_effects, ARRAY_SIZE(xg_effects),
				     port, chan, param,
				     chan->control[param],
				     EMUX_FX_FLAG_ADD);
}