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
struct input_ctx {struct cmd_bind_section* cmd_bind_sections; } ;
struct cmd_bind_section {struct cmd_bind_section* next; int /*<<< orphan*/  section; scalar_t__ owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 
 int /*<<< orphan*/  mp_input_disable_section (struct input_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_binds (struct cmd_bind_section*,int) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

void mp_input_remove_sections_by_owner(struct input_ctx *ictx, char *owner)
{
    input_lock(ictx);
    struct cmd_bind_section *bs = ictx->cmd_bind_sections;
    while (bs) {
        if (bs->owner && owner && strcmp(bs->owner, owner) == 0) {
            mp_input_disable_section(ictx, bs->section);
            remove_binds(bs, false);
            remove_binds(bs, true);
        }
        bs = bs->next;
    }
    input_unlock(ictx);
}