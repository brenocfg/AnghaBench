#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int time; int /*<<< orphan*/ * type; } ;
struct TYPE_5__ {int retrycount; scalar_t__ justid; scalar_t__ force; TYPE_1__ idle; } ;
typedef  TYPE_2__ xclaimOptions ;
typedef  int /*<<< orphan*/  smart_string ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_CMD_APPEND_SSTR_STATIC (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  redis_cmd_append_sstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redis_cmd_append_sstr_i64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  redis_cmd_append_sstr_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void append_xclaim_options(smart_string *cmd, xclaimOptions *opt) {
    /* IDLE/TIME long */
    if (opt->idle.type != NULL && opt->idle.time != -1) {
        redis_cmd_append_sstr(cmd, opt->idle.type, strlen(opt->idle.type));
        redis_cmd_append_sstr_i64(cmd, opt->idle.time);
    }

    /* RETRYCOUNT */
    if (opt->retrycount != -1) {
        REDIS_CMD_APPEND_SSTR_STATIC(cmd, "RETRYCOUNT");
        redis_cmd_append_sstr_long(cmd, opt->retrycount);
    }

    /* FORCE and JUSTID */
    if (opt->force)
        REDIS_CMD_APPEND_SSTR_STATIC(cmd, "FORCE");
    if (opt->justid)
        REDIS_CMD_APPEND_SSTR_STATIC(cmd, "JUSTID");
}