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
 int /*<<< orphan*/  ENGINE_CTRL_CHIL_SET_FORKCHECK ; 
 int /*<<< orphan*/  ENGINE_METHOD_ALL ; 
 int /*<<< orphan*/ * ENGINE_by_id (char const*) ; 
 int /*<<< orphan*/  ENGINE_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_default (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*) ; 
 int /*<<< orphan*/  TS_F_TS_CONF_SET_DEFAULT_ENGINE ; 
 int /*<<< orphan*/  TS_R_COULD_NOT_SET_ENGINE ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int TS_CONF_set_default_engine(const char *name)
{
    ENGINE *e = NULL;
    int ret = 0;

    if (strcmp(name, "builtin") == 0)
        return 1;

    if ((e = ENGINE_by_id(name)) == NULL)
        goto err;
    if (strcmp(name, "chil") == 0)
        ENGINE_ctrl(e, ENGINE_CTRL_CHIL_SET_FORKCHECK, 1, 0, 0);
    if (!ENGINE_set_default(e, ENGINE_METHOD_ALL))
        goto err;
    ret = 1;

 err:
    if (!ret) {
        TSerr(TS_F_TS_CONF_SET_DEFAULT_ENGINE, TS_R_COULD_NOT_SET_ENGINE);
        ERR_add_error_data(2, "engine:", name);
    }
    ENGINE_free(e);
    return ret;
}