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
struct osd_state {struct osd_object** objs; } ;
struct osd_object {int num_externals; int /*<<< orphan*/ * externals; int /*<<< orphan*/  ass; } ;

/* Variables and functions */
 int MAX_OSD_PARTS ; 
 int /*<<< orphan*/  destroy_ass_renderer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_external (int /*<<< orphan*/ *) ; 

void osd_destroy_backend(struct osd_state *osd)
{
    for (int n = 0; n < MAX_OSD_PARTS; n++) {
        struct osd_object *obj = osd->objs[n];
        destroy_ass_renderer(&obj->ass);
        for (int i = 0; i < obj->num_externals; i++)
            destroy_external(&obj->externals[i]);
        obj->num_externals = 0;
    }
}