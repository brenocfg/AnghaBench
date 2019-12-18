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
struct ak4113 {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ak4113_proc_regs_read ; 
 int /*<<< orphan*/  snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct ak4113*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ak4113_proc_init(struct ak4113 *ak4113)
{
	snd_card_ro_proc_new(ak4113->card, "ak4113", ak4113,
			     snd_ak4113_proc_regs_read);
}