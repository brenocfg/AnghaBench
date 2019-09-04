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
struct snd_jack {struct hda_jack_tbl* private_data; } ;
struct hda_jack_tbl {int /*<<< orphan*/ * jack; scalar_t__ nid; } ;

/* Variables and functions */

__attribute__((used)) static void hda_free_jack_priv(struct snd_jack *jack)
{
	struct hda_jack_tbl *jacks = jack->private_data;
	jacks->nid = 0;
	jacks->jack = NULL;
}