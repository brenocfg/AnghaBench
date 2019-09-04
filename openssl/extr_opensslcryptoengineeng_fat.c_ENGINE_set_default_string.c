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
 int /*<<< orphan*/  CONF_parse_list (char const*,char,int,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  ENGINE_F_ENGINE_SET_DEFAULT_STRING ; 
 int /*<<< orphan*/  ENGINE_R_INVALID_STRING ; 
 int ENGINE_set_default (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*) ; 
 int /*<<< orphan*/  int_def_cb ; 

int ENGINE_set_default_string(ENGINE *e, const char *def_list)
{
    unsigned int flags = 0;
    if (!CONF_parse_list(def_list, ',', 1, int_def_cb, &flags)) {
        ENGINEerr(ENGINE_F_ENGINE_SET_DEFAULT_STRING,
                  ENGINE_R_INVALID_STRING);
        ERR_add_error_data(2, "str=", def_list);
        return 0;
    }
    return ENGINE_set_default(e, flags);
}