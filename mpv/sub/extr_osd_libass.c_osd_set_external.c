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
struct osd_object {int num_externals; int changed; struct osd_external* externals; } ;
struct osd_external {void* id; int res_x; int res_y; scalar_t__ text; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct osd_object*,struct osd_external*,int,struct osd_external) ; 
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct osd_external*,int,int) ; 
 size_t OSDTYPE_EXTERNAL ; 
 int /*<<< orphan*/  destroy_external (struct osd_external*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  talloc_free (scalar_t__) ; 
 scalar_t__ talloc_strdup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  update_external (struct osd_state*,struct osd_object*,struct osd_external*) ; 

void osd_set_external(struct osd_state *osd, void *id, int res_x, int res_y,
                      char *text)
{
    pthread_mutex_lock(&osd->lock);
    struct osd_object *obj = osd->objs[OSDTYPE_EXTERNAL];
    struct osd_external *entry = 0;
    for (int n = 0; n < obj->num_externals; n++) {
        if (obj->externals[n].id == id) {
            entry = &obj->externals[n];
            break;
        }
    }
    if (!entry && !text)
        goto done;

    if (!entry) {
        struct osd_external new = { .id = id };
        MP_TARRAY_APPEND(obj, obj->externals, obj->num_externals, new);
        entry = &obj->externals[obj->num_externals - 1];
    }

    if (!text) {
        int index = entry - &obj->externals[0];
        destroy_external(entry);
        MP_TARRAY_REMOVE_AT(obj->externals, obj->num_externals, index);
        obj->changed = true;
        osd->want_redraw_notification = true;
        goto done;
    }

    if (!entry->text || strcmp(entry->text, text) != 0 ||
        entry->res_x != res_x || entry->res_y != res_y)
    {
        talloc_free(entry->text);
        entry->text = talloc_strdup(NULL, text);
        entry->res_x = res_x;
        entry->res_y = res_y;
        update_external(osd, obj, entry);
        obj->changed = true;
        osd->want_redraw_notification = true;
    }

done:
    pthread_mutex_unlock(&osd->lock);
}