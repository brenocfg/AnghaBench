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
struct mp_cmd_def {TYPE_1__* args; scalar_t__ vararg; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int MP_CMD_DEF_MAX_ARGS ; 

__attribute__((used)) static bool is_vararg(const struct mp_cmd_def *m, int i)
{
    return m->vararg && (i + 1 >= MP_CMD_DEF_MAX_ARGS || !m->args[i + 1].type);
}