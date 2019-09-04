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
struct osd_state {int want_redraw_notification; int /*<<< orphan*/  lock; struct osd_object** objs; } ;
struct osd_object {int osd_changed; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 size_t OSDTYPE_OSD ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_strdup (struct osd_object*,char const*) ; 

void osd_set_text(struct osd_state *osd, const char *text)
{
    pthread_mutex_lock(&osd->lock);
    struct osd_object *osd_obj = osd->objs[OSDTYPE_OSD];
    if (!text)
        text = "";
    if (strcmp(osd_obj->text, text) != 0) {
        talloc_free(osd_obj->text);
        osd_obj->text = talloc_strdup(osd_obj, text);
        osd_obj->osd_changed = true;
        osd->want_redraw_notification = true;
    }
    pthread_mutex_unlock(&osd->lock);
}