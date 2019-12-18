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
struct mp_cmd {int flags; } ;
typedef  int /*<<< orphan*/  bstr ;
struct TYPE_2__ {int remove; int add; scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ bstr_equals0 (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* cmd_flags ; 

__attribute__((used)) static bool apply_flag(struct mp_cmd *cmd, bstr str)
{
    for (int n = 0; cmd_flags[n].name; n++) {
        if (bstr_equals0(str, cmd_flags[n].name)) {
            cmd->flags = (cmd->flags & ~cmd_flags[n].remove) | cmd_flags[n].add;
            return true;
        }
    }
    return false;
}