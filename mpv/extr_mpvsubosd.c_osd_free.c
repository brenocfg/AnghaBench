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
struct osd_state {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  osd_destroy_backend (struct osd_state*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct osd_state*) ; 

void osd_free(struct osd_state *osd)
{
    if (!osd)
        return;
    osd_destroy_backend(osd);
    pthread_mutex_destroy(&osd->lock);
    talloc_free(osd);
}