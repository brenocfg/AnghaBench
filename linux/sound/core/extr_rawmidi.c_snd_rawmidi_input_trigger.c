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
struct snd_rawmidi_substream {TYPE_2__* runtime; TYPE_1__* ops; int /*<<< orphan*/  opened; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_work; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* trigger ) (struct snd_rawmidi_substream*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_rawmidi_substream*,int) ; 

__attribute__((used)) static void snd_rawmidi_input_trigger(struct snd_rawmidi_substream *substream, int up)
{
	if (!substream->opened)
		return;
	substream->ops->trigger(substream, up);
	if (!up)
		cancel_work_sync(&substream->runtime->event_work);
}