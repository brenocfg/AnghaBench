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
struct mp_cmd_ctx {struct cmd_list_ctx* on_completion_priv; } ;
struct cmd_list_ctx {int completed_recursive; int /*<<< orphan*/  current; scalar_t__ current_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  continue_cmd_list (struct cmd_list_ctx*) ; 
 scalar_t__ pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 

__attribute__((used)) static void on_cmd_list_sub_completion(struct mp_cmd_ctx *cmd)
{
    struct cmd_list_ctx *list = cmd->on_completion_priv;

    if (list->current_valid && pthread_equal(list->current, pthread_self())) {
        list->completed_recursive = true;
    } else {
        continue_cmd_list(list);
    }
}