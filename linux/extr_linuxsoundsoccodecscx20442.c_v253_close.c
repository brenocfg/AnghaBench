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
struct tty_struct {struct snd_soc_component* disc_data; } ;
struct snd_soc_component {TYPE_1__* card; } ;
struct cx20442_priv {int /*<<< orphan*/ * tty; } ;
struct TYPE_2__ {scalar_t__ pop_time; } ;

/* Variables and functions */
 struct cx20442_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void v253_close(struct tty_struct *tty)
{
	struct snd_soc_component *component = tty->disc_data;
	struct cx20442_priv *cx20442;

	tty->disc_data = NULL;

	if (!component)
		return;

	cx20442 = snd_soc_component_get_drvdata(component);

	/* Prevent the codec driver from further accessing the modem */
	cx20442->tty = NULL;
	component->card->pop_time = 0;
}