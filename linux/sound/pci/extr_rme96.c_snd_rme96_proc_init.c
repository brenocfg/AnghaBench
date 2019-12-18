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
struct rme96 {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct rme96*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rme96_proc_read ; 

__attribute__((used)) static void snd_rme96_proc_init(struct rme96 *rme96)
{
	snd_card_ro_proc_new(rme96->card, "rme96", rme96, snd_rme96_proc_read);
}