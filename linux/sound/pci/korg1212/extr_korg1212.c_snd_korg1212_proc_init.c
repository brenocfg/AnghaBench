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
struct snd_korg1212 {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct snd_korg1212*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_korg1212_proc_read ; 

__attribute__((used)) static void snd_korg1212_proc_init(struct snd_korg1212 *korg1212)
{
	snd_card_ro_proc_new(korg1212->card, "korg1212", korg1212,
			     snd_korg1212_proc_read);
}