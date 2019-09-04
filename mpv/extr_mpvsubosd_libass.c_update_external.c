#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct osd_style_opts {int dummy; } ;
struct osd_state {TYPE_1__* opts; } ;
struct osd_object {int dummy; } ;
struct TYPE_17__ {TYPE_12__* track; int /*<<< orphan*/  res_y; int /*<<< orphan*/  res_x; } ;
struct osd_external {TYPE_4__ ass; int /*<<< orphan*/  res_y; int /*<<< orphan*/  res_x; int /*<<< orphan*/  text; } ;
struct TYPE_15__ {scalar_t__ len; } ;
typedef  TYPE_2__ bstr ;
struct TYPE_16__ {struct osd_style_opts* defaults; } ;
struct TYPE_14__ {struct osd_style_opts const* osd_style; } ;
struct TYPE_13__ {int PlayResY; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_osd_ass_event (TYPE_12__*,char*,char*) ; 
 TYPE_2__ bstr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr_split_tok (TYPE_2__,char*,TYPE_2__*,TYPE_2__*) ; 
 char* bstrdup0 (int /*<<< orphan*/ *,TYPE_2__) ; 
 int /*<<< orphan*/  clear_ass (TYPE_4__*) ; 
 int /*<<< orphan*/  create_ass_track (struct osd_state*,struct osd_object*,TYPE_4__*) ; 
 int /*<<< orphan*/  get_style (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  mp_ass_set_style (int /*<<< orphan*/ ,int,struct osd_style_opts const*) ; 
 TYPE_3__ osd_style_conf ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static void update_external(struct osd_state *osd, struct osd_object *obj,
                            struct osd_external *ext)
{
    bstr t = bstr0(ext->text);
    if (!t.len)
        return;
    ext->ass.res_x = ext->res_x;
    ext->ass.res_y = ext->res_y;
    create_ass_track(osd, obj, &ext->ass);

    clear_ass(&ext->ass);

    int resy = ext->ass.track->PlayResY;
    mp_ass_set_style(get_style(&ext->ass, "OSD"), resy, osd->opts->osd_style);

    // Some scripts will reference this style name with \r tags.
    const struct osd_style_opts *def = osd_style_conf.defaults;
    mp_ass_set_style(get_style(&ext->ass, "Default"), resy, def);

    while (t.len) {
        bstr line;
        bstr_split_tok(t, "\n", &line, &t);
        if (line.len) {
            char *tmp = bstrdup0(NULL, line);
            add_osd_ass_event(ext->ass.track, "OSD", tmp);
            talloc_free(tmp);
        }
    }
}