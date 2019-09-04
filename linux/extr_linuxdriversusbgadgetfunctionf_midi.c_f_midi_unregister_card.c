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
struct f_midi {int /*<<< orphan*/ * card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void f_midi_unregister_card(struct f_midi *midi)
{
	if (midi->card) {
		snd_card_free(midi->card);
		midi->card = NULL;
	}
}