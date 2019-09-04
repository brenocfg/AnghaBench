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
struct TYPE_4__ {int /*<<< orphan*/  option_value; int /*<<< orphan*/  name_flags; } ;
typedef  TYPE_1__ ssl_switch_tbl ;
typedef  int /*<<< orphan*/  ssl_conf_cmd_tbl ;
typedef  int /*<<< orphan*/  SSL_CONF_CTX ;

/* Variables and functions */
 size_t OSSL_NELEM (TYPE_1__*) ; 
 TYPE_1__* ssl_cmd_switches ; 
 int /*<<< orphan*/  const* ssl_conf_cmds ; 
 int /*<<< orphan*/  ssl_set_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ctrl_switch_option(SSL_CONF_CTX *cctx, const ssl_conf_cmd_tbl * cmd)
{
    /* Find index of command in table */
    size_t idx = cmd - ssl_conf_cmds;
    const ssl_switch_tbl *scmd;
    /* Sanity check index */
    if (idx >= OSSL_NELEM(ssl_cmd_switches))
        return 0;
    /* Obtain switches entry with same index */
    scmd = ssl_cmd_switches + idx;
    ssl_set_option(cctx, scmd->name_flags, scmd->option_value, 1);
    return 1;
}