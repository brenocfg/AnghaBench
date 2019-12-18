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
struct ak4114 {int /*<<< orphan*/  work; int /*<<< orphan*/  wq_processing; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ak4114*) ; 

__attribute__((used)) static void snd_ak4114_free(struct ak4114 *chip)
{
	atomic_inc(&chip->wq_processing);	/* don't schedule new work */
	cancel_delayed_work_sync(&chip->work);
	kfree(chip);
}