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
struct osd_state {int dummy; } ;
struct osd_object {int osd_changed; int /*<<< orphan*/  ass; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_ass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_osd_text (struct osd_state*,struct osd_object*) ; 
 int /*<<< orphan*/  update_progbar (struct osd_state*,struct osd_object*) ; 

__attribute__((used)) static void update_osd(struct osd_state *osd, struct osd_object *obj)
{
    obj->osd_changed = false;
    clear_ass(&obj->ass);
    update_osd_text(osd, obj);
    update_progbar(osd, obj);
}