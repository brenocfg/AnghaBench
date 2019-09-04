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
struct osd_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  track; } ;
struct osd_object {int /*<<< orphan*/ * text; TYPE_1__ ass; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_osd_ass_event_escaped (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_osd_ass (struct osd_state*,struct osd_object*) ; 

__attribute__((used)) static void update_osd_text(struct osd_state *osd, struct osd_object *obj)
{

    if (!obj->text[0])
        return;

    prepare_osd_ass(osd, obj);
    add_osd_ass_event_escaped(obj->ass.track, "OSD", obj->text);
}