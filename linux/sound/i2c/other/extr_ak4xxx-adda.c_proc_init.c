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
struct snd_akm4xxx {int /*<<< orphan*/  name; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_regs_read ; 
 int snd_card_ro_proc_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_akm4xxx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_init(struct snd_akm4xxx *ak)
{
	return snd_card_ro_proc_new(ak->card, ak->name, ak, proc_regs_read);
}