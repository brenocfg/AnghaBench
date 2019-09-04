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
struct MPContext {int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  mp_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_input_get_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_input_read_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_set_timeout (struct MPContext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_command (struct MPContext*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void mp_process_input(struct MPContext *mpctx)
{
    for (;;) {
        mp_cmd_t *cmd = mp_input_read_cmd(mpctx->input);
        if (!cmd)
            break;
        run_command(mpctx, cmd, NULL, NULL, NULL);
    }
    mp_set_timeout(mpctx, mp_input_get_delay(mpctx->input));
}