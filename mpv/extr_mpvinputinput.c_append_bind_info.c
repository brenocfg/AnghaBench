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
struct mp_cmd {int /*<<< orphan*/  original; } ;
struct input_ctx {int dummy; } ;
struct cmd_bind {scalar_t__ is_builtin; int /*<<< orphan*/  location; TYPE_1__* owner; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  bstr ;
struct TYPE_2__ {int /*<<< orphan*/  section; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 struct mp_cmd* mp_input_parse_cmd (struct input_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* talloc_asprintf_append (char*,char*,...) ; 
 int /*<<< orphan*/  talloc_free (struct mp_cmd*) ; 

__attribute__((used)) static void append_bind_info(struct input_ctx *ictx, char **pmsg,
                             struct cmd_bind *bind)
{
    char *msg = *pmsg;
    struct mp_cmd *cmd = mp_input_parse_cmd(ictx, bstr0(bind->cmd),
                                            bind->location);
    bstr stripped = cmd ? cmd->original : bstr0(bind->cmd);
    msg = talloc_asprintf_append(msg, " '%.*s'", BSTR_P(stripped));
    if (!cmd)
        msg = talloc_asprintf_append(msg, " (invalid)");
    if (strcmp(bind->owner->section, "default") != 0)
        msg = talloc_asprintf_append(msg, " in section {%s}",
                                     bind->owner->section);
    msg = talloc_asprintf_append(msg, " in %s", bind->location);
    if (bind->is_builtin)
        msg = talloc_asprintf_append(msg, " (default)");
    talloc_free(cmd);
    *pmsg = msg;
}