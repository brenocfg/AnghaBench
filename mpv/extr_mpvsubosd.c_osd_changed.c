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
struct osd_state {int want_redraw_notification; int /*<<< orphan*/  lock; int /*<<< orphan*/  opts_cache; TYPE_1__** objs; } ;
struct TYPE_2__ {int osd_changed; } ;

/* Variables and functions */
 size_t OSDTYPE_OSD ; 
 int /*<<< orphan*/  m_config_cache_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void osd_changed(struct osd_state *osd)
{
    pthread_mutex_lock(&osd->lock);
    osd->objs[OSDTYPE_OSD]->osd_changed = true;
    osd->want_redraw_notification = true;
    // Done here for a lack of a better place.
    m_config_cache_update(osd->opts_cache);
    pthread_mutex_unlock(&osd->lock);
}