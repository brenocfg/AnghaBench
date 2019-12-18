#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int name_flags; int namelen; int /*<<< orphan*/  option_value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ssl_flag_tbl ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_2__ SSL_CONF_CTX ;

/* Variables and functions */
 int SSL_TFLAG_BOTH ; 
 int /*<<< orphan*/  ssl_set_option (TYPE_2__*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int ssl_match_option(SSL_CONF_CTX *cctx, const ssl_flag_tbl *tbl,
                            const char *name, int namelen, int onoff)
{
    /* If name not relevant for context skip */
    if (!(cctx->flags & tbl->name_flags & SSL_TFLAG_BOTH))
        return 0;
    if (namelen == -1) {
        if (strcmp(tbl->name, name))
            return 0;
    } else if (tbl->namelen != namelen || strncasecmp(tbl->name, name, namelen))
        return 0;
    ssl_set_option(cctx, tbl->name_flags, tbl->option_value, onoff);
    return 1;
}