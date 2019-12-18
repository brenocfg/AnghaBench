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
struct input_ctx {char* mouse_section; } ;
struct cmd_bind {TYPE_1__* owner; } ;
struct TYPE_2__ {char* section; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_KEY_MOUSE_LEAVE ; 
 int /*<<< orphan*/  MP_KEY_MOUSE_MOVE ; 
 int /*<<< orphan*/  MP_TRACE (struct input_ctx*,char*,char*,char*) ; 
 struct cmd_bind* find_any_bind_for_key (struct input_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cmd_from_keys (struct input_ctx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_input_queue_cmd (struct input_ctx*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void update_mouse_section(struct input_ctx *ictx)
{
    struct cmd_bind *bind =
        find_any_bind_for_key(ictx, NULL, MP_KEY_MOUSE_MOVE);

    char *new_section = bind ? bind->owner->section : "default";

    char *old = ictx->mouse_section;
    ictx->mouse_section = new_section;

    if (strcmp(old, ictx->mouse_section) != 0) {
        MP_TRACE(ictx, "input: switch section %s -> %s\n",
                 old, ictx->mouse_section);
        mp_input_queue_cmd(ictx, get_cmd_from_keys(ictx, old, MP_KEY_MOUSE_LEAVE));
    }
}