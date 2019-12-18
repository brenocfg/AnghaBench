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
struct mp_hwdec_devices {int /*<<< orphan*/  lock; int /*<<< orphan*/  load_api; int /*<<< orphan*/  num_hwctxs; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct mp_hwdec_devices*) ; 

void hwdec_devices_destroy(struct mp_hwdec_devices *devs)
{
    if (!devs)
        return;
    assert(!devs->num_hwctxs); // must have been hwdec_devices_remove()ed
    assert(!devs->load_api); // must have been unset
    pthread_mutex_destroy(&devs->lock);
    talloc_free(devs);
}