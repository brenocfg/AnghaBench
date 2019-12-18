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
struct snd_seq_oss_arg {struct snd_emux_port* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct snd_emux_port {TYPE_1__ chset; struct snd_emux* emu; } ;
struct snd_emux {int /*<<< orphan*/  sflist; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SF_CLIENT_NO (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_emux_dec_count (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emux_sounds_off_all (struct snd_emux_port*) ; 
 int /*<<< orphan*/  snd_seq_event_port_detach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soundfont_close_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snd_emux_close_seq_oss(struct snd_seq_oss_arg *arg)
{
	struct snd_emux *emu;
	struct snd_emux_port *p;

	if (snd_BUG_ON(!arg))
		return -ENXIO;
	p = arg->private_data;
	if (snd_BUG_ON(!p))
		return -ENXIO;

	emu = p->emu;
	if (snd_BUG_ON(!emu))
		return -ENXIO;

	snd_emux_sounds_off_all(p);
	snd_soundfont_close_check(emu->sflist, SF_CLIENT_NO(p->chset.port));
	snd_seq_event_port_detach(p->chset.client, p->chset.port);
	snd_emux_dec_count(emu);

	return 0;
}