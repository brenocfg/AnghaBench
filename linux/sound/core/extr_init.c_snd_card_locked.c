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

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_mutex ; 
 int /*<<< orphan*/  snd_cards_lock ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

int snd_card_locked(int card)
{
	int locked;

	mutex_lock(&snd_card_mutex);
	locked = test_bit(card, snd_cards_lock);
	mutex_unlock(&snd_card_mutex);
	return locked;
}