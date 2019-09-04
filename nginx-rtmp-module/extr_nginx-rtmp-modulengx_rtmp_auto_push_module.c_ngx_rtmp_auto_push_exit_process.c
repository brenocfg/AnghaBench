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
typedef  int /*<<< orphan*/  ngx_cycle_t ;

/* Variables and functions */

__attribute__((used)) static void
ngx_rtmp_auto_push_exit_process(ngx_cycle_t *cycle)
{
#if (NGX_HAVE_UNIX_DOMAIN)
    ngx_rtmp_auto_push_conf_t  *apcf;
    u_char                      path[NGX_MAX_PATH];

    apcf = (ngx_rtmp_auto_push_conf_t *) ngx_get_conf(cycle->conf_ctx,
                                                    ngx_rtmp_auto_push_module);
    if (apcf->auto_push == 0) {
        return;
    }
    *ngx_snprintf(path, sizeof(path),
                  "%V/" NGX_RTMP_AUTO_PUSH_SOCKNAME ".%i",
                  &apcf->socket_dir, ngx_process_slot)
         = 0;

    ngx_delete_file(path);

#endif
}