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
struct sub_bitmaps {int dummy; } ;
struct osd_state {int want_redraw_notification; int /*<<< orphan*/  lock; TYPE_1__** objs; } ;
struct TYPE_2__ {int vo_change_id; struct sub_bitmaps* external2; } ;

/* Variables and functions */
 size_t OSDTYPE_EXTERNAL2 ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void osd_set_external2(struct osd_state *osd, struct sub_bitmaps *imgs)
{
    pthread_mutex_lock(&osd->lock);
    osd->objs[OSDTYPE_EXTERNAL2]->external2 = imgs;
    osd->objs[OSDTYPE_EXTERNAL2]->vo_change_id += 1;
    osd->want_redraw_notification = true;
    pthread_mutex_unlock(&osd->lock);
}