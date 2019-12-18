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
struct input_ctx {char* mouse_section; int num_active_sections; int /*<<< orphan*/  mouse_vo_y; int /*<<< orphan*/  mouse_vo_x; struct active_section* active_sections; int /*<<< orphan*/  last_key_down; } ;
struct cmd_bind_section {int /*<<< orphan*/  mouse_area; scalar_t__ mouse_area_set; } ;
struct cmd_bind {scalar_t__ is_builtin; struct cmd_bind_section* owner; } ;
struct active_section {char* name; int flags; } ;

/* Variables and functions */
 int MP_INPUT_EXCLUSIVE ; 
 int MP_INPUT_ON_TOP ; 
 int MP_KEY_DEPENDS_ON_MOUSE_POS (int) ; 
 scalar_t__ MP_KEY_IS_MOUSE_BTN_SINGLE (int /*<<< orphan*/ ) ; 
 struct cmd_bind* find_bind_for_key_section (struct input_ctx*,char*,int) ; 
 scalar_t__ test_rect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cmd_bind *find_any_bind_for_key(struct input_ctx *ictx,
                                              char *force_section, int code)
{
    if (force_section)
        return find_bind_for_key_section(ictx, force_section, code);

    bool use_mouse = MP_KEY_DEPENDS_ON_MOUSE_POS(code);

    // First look whether a mouse section is capturing all mouse input
    // exclusively (regardless of the active section stack order).
    if (use_mouse && MP_KEY_IS_MOUSE_BTN_SINGLE(ictx->last_key_down)) {
        struct cmd_bind *bind =
            find_bind_for_key_section(ictx, ictx->mouse_section, code);
        if (bind)
            return bind;
    }

    struct cmd_bind *best_bind = NULL;
    for (int i = ictx->num_active_sections - 1; i >= 0; i--) {
        struct active_section *s = &ictx->active_sections[i];
        struct cmd_bind *bind = find_bind_for_key_section(ictx, s->name, code);
        if (bind) {
            struct cmd_bind_section *bs = bind->owner;
            if (!use_mouse || (bs->mouse_area_set && test_rect(&bs->mouse_area,
                                                               ictx->mouse_vo_x,
                                                               ictx->mouse_vo_y)))
            {
                if (!best_bind || (best_bind->is_builtin && !bind->is_builtin))
                    best_bind = bind;
            }
        }
        if (s->flags & MP_INPUT_EXCLUSIVE)
            break;
        if (best_bind && (s->flags & MP_INPUT_ON_TOP))
            break;
    }

    return best_bind;
}