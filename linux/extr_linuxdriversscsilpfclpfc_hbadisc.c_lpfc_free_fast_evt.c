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
struct lpfc_hba {int /*<<< orphan*/  fast_event_count; } ;
struct lpfc_fast_path_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lpfc_fast_path_event*) ; 

void
lpfc_free_fast_evt(struct lpfc_hba *phba,
		struct lpfc_fast_path_event *evt) {

	atomic_dec(&phba->fast_event_count);
	kfree(evt);
}