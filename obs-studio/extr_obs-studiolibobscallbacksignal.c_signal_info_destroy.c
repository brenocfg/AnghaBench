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
struct signal_info {int /*<<< orphan*/  callbacks; int /*<<< orphan*/  func; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct signal_info*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decl_info_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void signal_info_destroy(struct signal_info *si)
{
	if (si) {
		pthread_mutex_destroy(&si->mutex);
		decl_info_free(&si->func);
		da_free(si->callbacks);
		bfree(si);
	}
}