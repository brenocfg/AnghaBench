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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ SSL_CONF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CONF_FLAG_CMDLINE ; 
 int /*<<< orphan*/  SSL_CONF_FLAG_FILE ; 
 int SSL_CONF_cmd (TYPE_1__*,char const*,char const*) ; 

int SSL_CONF_cmd_argv(SSL_CONF_CTX *cctx, int *pargc, char ***pargv)
{
    int rv;
    const char *arg = NULL, *argn;

    if (pargc != NULL && *pargc == 0)
        return 0;
    if (pargc == NULL || *pargc > 0)
        arg = **pargv;
    if (arg == NULL)
        return 0;
    if (pargc == NULL || *pargc > 1)
        argn = (*pargv)[1];
    else
        argn = NULL;
    cctx->flags &= ~SSL_CONF_FLAG_FILE;
    cctx->flags |= SSL_CONF_FLAG_CMDLINE;
    rv = SSL_CONF_cmd(cctx, arg, argn);
    if (rv > 0) {
        /* Success: update pargc, pargv */
        (*pargv) += rv;
        if (pargc)
            (*pargc) -= rv;
        return rv;
    }
    /* Unknown switch: indicate no arguments processed */
    if (rv == -2)
        return 0;
    /* Some error occurred processing command, return fatal error */
    if (rv == 0)
        return -1;
    return rv;
}