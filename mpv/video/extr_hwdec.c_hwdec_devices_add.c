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
struct mp_hwdec_devices {int /*<<< orphan*/  lock; int /*<<< orphan*/  num_hwctxs; int /*<<< orphan*/  hwctxs; } ;
struct mp_hwdec_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct mp_hwdec_devices*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_hwdec_ctx*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void hwdec_devices_add(struct mp_hwdec_devices *devs, struct mp_hwdec_ctx *ctx)
{
    pthread_mutex_lock(&devs->lock);
    MP_TARRAY_APPEND(devs, devs->hwctxs, devs->num_hwctxs, ctx);
    pthread_mutex_unlock(&devs->lock);
}