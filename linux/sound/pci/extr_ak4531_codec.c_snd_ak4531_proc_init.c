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
struct snd_ak4531 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ak4531_proc_read ; 
 int /*<<< orphan*/  snd_card_ro_proc_new (struct snd_card*,char*,struct snd_ak4531*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snd_ak4531_proc_init(struct snd_card *card, struct snd_ak4531 *ak4531)
{
	snd_card_ro_proc_new(card, "ak4531", ak4531, snd_ak4531_proc_read);
}