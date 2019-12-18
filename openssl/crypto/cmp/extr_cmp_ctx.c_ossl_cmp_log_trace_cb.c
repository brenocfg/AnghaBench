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
struct TYPE_2__ {scalar_t__ log_verbosity; int /*<<< orphan*/  (* log_cb ) (char*,char*,int,scalar_t__,char const*) ;} ;
typedef  scalar_t__ OSSL_CMP_severity ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int OSSL_TRACE_CTRL_WRITE ; 
 char* ossl_cmp_log_parse_metadata (char const*,scalar_t__*,char**,char**,int*) ; 
 int /*<<< orphan*/  stub1 (char*,char*,int,scalar_t__,char const*) ; 

__attribute__((used)) static size_t ossl_cmp_log_trace_cb(const char *buf, size_t cnt,
                                    int category, int cmd, void *vdata)
{
    OSSL_CMP_CTX *ctx = vdata;
    const char *prefix_msg;
    OSSL_CMP_severity level = -1;
    char *func = NULL;
    char *file = NULL;
    int line = 0;

    if (buf == NULL || cnt == 0 || cmd != OSSL_TRACE_CTRL_WRITE || ctx == NULL)
        return 0;
    if (ctx->log_cb == NULL)
        return 1; /* silently drop message */

    prefix_msg = ossl_cmp_log_parse_metadata(buf, &level, &func, &file, &line);

    if (level > ctx->log_verbosity) /* excludes the case level is unknown */
        goto end; /* suppress output since severity is not sufficient */

    if (!ctx->log_cb(func != NULL ? func : "(no func)",
                     file != NULL ? file : "(no file)",
                     line, level, prefix_msg))
        cnt = 0;

 end:
    OPENSSL_free(func);
    OPENSSL_free(file);
    return cnt;
}