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
struct tls_root_ctx {scalar_t__ crl_last_size; int crl_last_mtime; } ;
struct TYPE_3__ {int st_mtime; scalar_t__ st_size; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ platform_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  backend_tls_ctx_reload_crl (struct tls_root_ctx*,char const*,char const*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ platform_stat (char const*,TYPE_1__*) ; 

__attribute__((used)) static void
tls_ctx_reload_crl(struct tls_root_ctx *ssl_ctx, const char *crl_file,
                   const char *crl_file_inline)
{
    /* if something goes wrong with stat(), we'll store 0 as mtime */
    platform_stat_t crl_stat = {0};

    /*
     * an inline CRL can't change at runtime, therefore there is no need to
     * reload it. It will be reloaded upon config change + SIGHUP.
     * Use always '1' as dummy timestamp in this case: it will trigger the
     * first load, but will prevent any future reload.
     */
    if (crl_file_inline)
    {
        crl_stat.st_mtime = 1;
    }
    else if (platform_stat(crl_file, &crl_stat) < 0)
    {
        msg(M_WARN, "WARNING: Failed to stat CRL file, not (re)loading CRL.");
        return;
    }

    /*
     * Store the CRL if this is the first time or if the file was changed since
     * the last load.
     * Note: Windows does not support tv_nsec.
     */
    if ((ssl_ctx->crl_last_size == crl_stat.st_size)
        && (ssl_ctx->crl_last_mtime == crl_stat.st_mtime))
    {
        return;
    }

    ssl_ctx->crl_last_mtime = crl_stat.st_mtime;
    ssl_ctx->crl_last_size = crl_stat.st_size;
    backend_tls_ctx_reload_crl(ssl_ctx, crl_file, crl_file_inline);
}