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
struct snd_card {int dummy; } ;
struct lx6464es {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lx_proc_levels_read ; 
 int snd_card_ro_proc_new (struct snd_card*,char*,struct lx6464es*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lx_proc_create(struct snd_card *card, struct lx6464es *chip)
{
	return snd_card_ro_proc_new(card, "levels", chip, lx_proc_levels_read);
}