#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_cmd_ctx {int success; TYPE_2__* args; scalar_t__ priv; struct MPContext* mpctx; } ;
struct MPContext {int /*<<< orphan*/  input; } ;
struct TYPE_3__ {char* s; } ;
struct TYPE_4__ {TYPE_1__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*,char const*) ; 
 int MP_INPUT_RELEASE_ALL ; 
 int MP_KEY_STATE_UP ; 
 int mp_input_get_key_from_name (char const*) ; 
 int /*<<< orphan*/  mp_input_put_key_artificial (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cmd_key(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;
    int action = *(int *)cmd->priv;

    const char *key_name = cmd->args[0].v.s;
    if (key_name[0] == '\0' && action == MP_KEY_STATE_UP) {
        mp_input_put_key_artificial(mpctx->input, MP_INPUT_RELEASE_ALL);
    } else {
        int code = mp_input_get_key_from_name(key_name);
        if (code < 0) {
            MP_ERR(mpctx, "%s is not a valid input name.\n", key_name);
            cmd->success = false;
            return;
        }
        mp_input_put_key_artificial(mpctx->input, code | action);
    }
}