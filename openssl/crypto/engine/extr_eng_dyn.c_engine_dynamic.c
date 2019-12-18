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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_FLAGS_BY_ID_COPY ; 
 int /*<<< orphan*/  ENGINE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_new () ; 
 int /*<<< orphan*/  ENGINE_set_cmd_defns (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_ctrl_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_finish_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_init_function (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_set_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dynamic_cmd_defns ; 
 int /*<<< orphan*/  dynamic_ctrl ; 
 int /*<<< orphan*/  dynamic_finish ; 
 int /*<<< orphan*/  dynamic_init ; 
 int /*<<< orphan*/  engine_dynamic_id ; 
 int /*<<< orphan*/  engine_dynamic_name ; 

__attribute__((used)) static ENGINE *engine_dynamic(void)
{
    ENGINE *ret = ENGINE_new();
    if (ret == NULL)
        return NULL;
    if (!ENGINE_set_id(ret, engine_dynamic_id) ||
        !ENGINE_set_name(ret, engine_dynamic_name) ||
        !ENGINE_set_init_function(ret, dynamic_init) ||
        !ENGINE_set_finish_function(ret, dynamic_finish) ||
        !ENGINE_set_ctrl_function(ret, dynamic_ctrl) ||
        !ENGINE_set_flags(ret, ENGINE_FLAGS_BY_ID_COPY) ||
        !ENGINE_set_cmd_defns(ret, dynamic_cmd_defns)) {
        ENGINE_free(ret);
        return NULL;
    }
    return ret;
}