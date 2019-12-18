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
struct input_ctx {int dummy; } ;
struct cmd_bind_section {scalar_t__ owner; scalar_t__ section; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char*) ; 
 struct cmd_bind_section* get_bind_section (struct input_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 
 int /*<<< orphan*/  mp_input_disable_section (struct input_ctx*,char*) ; 
 int /*<<< orphan*/  parse_config (struct input_ctx*,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  remove_binds (struct cmd_bind_section*,int) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  talloc_free (scalar_t__) ; 
 scalar_t__ talloc_strdup (struct cmd_bind_section*,char*) ; 

void mp_input_define_section(struct input_ctx *ictx, char *name, char *location,
                             char *contents, bool builtin, char *owner)
{
    if (!name || !name[0])
        return; // parse_config() changes semantics with restrict_section==empty
    input_lock(ictx);
    // Delete:
    struct cmd_bind_section *bs = get_bind_section(ictx, bstr0(name));
    if ((!bs->owner || (owner && strcmp(bs->owner, owner) != 0)) &&
        strcmp(bs->section, "default") != 0)
    {
        talloc_free(bs->owner);
        bs->owner = talloc_strdup(bs, owner);
    }
    remove_binds(bs, builtin);
    if (contents && contents[0]) {
        // Redefine:
        parse_config(ictx, builtin, bstr0(contents), location, name);
    } else {
        // Disable:
        mp_input_disable_section(ictx, name);
    }
    input_unlock(ictx);
}