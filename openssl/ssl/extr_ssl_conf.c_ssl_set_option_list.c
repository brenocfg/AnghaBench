#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssl_flag_tbl ;
struct TYPE_3__ {size_t ntbl; int /*<<< orphan*/ * tbl; } ;
typedef  TYPE_1__ SSL_CONF_CTX ;

/* Variables and functions */
 scalar_t__ ssl_match_option (TYPE_1__*,int /*<<< orphan*/  const*,char const*,int,int) ; 

__attribute__((used)) static int ssl_set_option_list(const char *elem, int len, void *usr)
{
    SSL_CONF_CTX *cctx = usr;
    size_t i;
    const ssl_flag_tbl *tbl;
    int onoff = 1;
    /*
     * len == -1 indicates not being called in list context, just for single
     * command line switches, so don't allow +, -.
     */
    if (elem == NULL)
        return 0;
    if (len != -1) {
        if (*elem == '+') {
            elem++;
            len--;
            onoff = 1;
        } else if (*elem == '-') {
            elem++;
            len--;
            onoff = 0;
        }
    }
    for (i = 0, tbl = cctx->tbl; i < cctx->ntbl; i++, tbl++) {
        if (ssl_match_option(cctx, tbl, elem, len, onoff))
            return 1;
    }
    return 0;
}