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
struct input_ctx {int num_active_sections; struct active_section* active_sections; } ;
struct cmd_bind_section {int /*<<< orphan*/  mouse_area; scalar_t__ mouse_area_set; } ;
struct active_section {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 struct cmd_bind_section* get_bind_section (struct input_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 
 scalar_t__ test_rect (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static bool test_mouse(struct input_ctx *ictx, int x, int y, int rej_flags)
{
    input_lock(ictx);
    bool res = false;
    for (int i = 0; i < ictx->num_active_sections; i++) {
        struct active_section *as = &ictx->active_sections[i];
        if (as->flags & rej_flags)
            continue;
        struct cmd_bind_section *s = get_bind_section(ictx, bstr0(as->name));
        if (s->mouse_area_set && test_rect(&s->mouse_area, x, y)) {
            res = true;
            break;
        }
    }
    input_unlock(ictx);
    return res;
}