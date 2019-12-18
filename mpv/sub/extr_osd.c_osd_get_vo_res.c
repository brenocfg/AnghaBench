#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct osd_state {int /*<<< orphan*/  lock; TYPE_1__** objs; } ;
struct mp_osd_res {int dummy; } ;
struct TYPE_2__ {struct mp_osd_res vo_res; } ;

/* Variables and functions */
 size_t OSDTYPE_OSD ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

struct mp_osd_res osd_get_vo_res(struct osd_state *osd)
{
    pthread_mutex_lock(&osd->lock);
    // Any OSDTYPE is fine; but it mustn't be a subtitle one (can have lower res.)
    struct mp_osd_res res = osd->objs[OSDTYPE_OSD]->vo_res;
    pthread_mutex_unlock(&osd->lock);
    return res;
}