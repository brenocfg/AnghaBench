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
struct cx20442_priv {struct tty_struct* tty; } ;
struct TYPE_2__ {int pop_time; } ;

/* Variables and functions */
 struct cx20442_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void v253_receive(struct tty_struct *tty,
				const unsigned char *cp, char *fp, int count)
{
	struct snd_soc_component *component = tty->disc_data;
	struct cx20442_priv *cx20442;

	if (!component)
		return;

	cx20442 = snd_soc_component_get_drvdata(component);

	if (!cx20442->tty) {
		/* First modem response, complete setup procedure */

		/* Set up codec driver access to modem controls */
		cx20442->tty = tty;
		component->card->pop_time = 1;
	}
}