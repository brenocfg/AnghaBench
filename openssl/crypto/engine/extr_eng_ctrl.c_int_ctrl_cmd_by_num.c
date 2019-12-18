#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int cmd_num; } ;
typedef  TYPE_1__ ENGINE_CMD_DEFN ;

/* Variables and functions */
 int /*<<< orphan*/  int_ctrl_cmd_is_null (TYPE_1__ const*) ; 

__attribute__((used)) static int int_ctrl_cmd_by_num(const ENGINE_CMD_DEFN *defn, unsigned int num)
{
    int idx = 0;
    /*
     * NB: It is stipulated that 'cmd_defn' lists are ordered by cmd_num. So
     * our searches don't need to take any longer than necessary.
     */
    while (!int_ctrl_cmd_is_null(defn) && (defn->cmd_num < num)) {
        idx++;
        defn++;
    }
    if (defn->cmd_num == num)
        return idx;
    /* The given cmd_num wasn't found */
    return -1;
}