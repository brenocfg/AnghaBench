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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_auto_push_init_process(ngx_cycle_t *cycle)
{
#if (NGX_HAVE_UNIX_DOMAIN)
    ngx_rtmp_auto_push_conf_t  *apcf;
    ngx_listening_t            *ls, *lss;
    struct sockaddr_un         *saun;
    int                         reuseaddr;
    ngx_socket_t                s;
    size_t                      n;
    ngx_file_info_t             fi;

    if (ngx_process != NGX_PROCESS_WORKER) {
        return NGX_OK;
    }

    apcf = (ngx_rtmp_auto_push_conf_t *) ngx_get_conf(cycle->conf_ctx,
                                                    ngx_rtmp_auto_push_module);
    if (apcf->auto_push == 0) {
        return NGX_OK;
    }

    next_publish = ngx_rtmp_publish;
    ngx_rtmp_publish = ngx_rtmp_auto_push_publish;

    next_delete_stream = ngx_rtmp_delete_stream;
    ngx_rtmp_delete_stream = ngx_rtmp_auto_push_delete_stream;

    reuseaddr = 1;
    s = (ngx_socket_t) -1;

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, cycle->log, 0,
            "auto_push: creating sockets");

    /*TODO: clone all RTMP listenings? */
    ls = cycle->listening.elts;
    lss = NULL;
    for (n = 0; n < cycle->listening.nelts; ++n, ++ls) {
        if (ls->handler == ngx_rtmp_init_connection) {
            lss = ls;
            break;
        }
    }

    if (lss == NULL) {
        return NGX_OK;
    }

    ls = ngx_array_push(&cycle->listening);
    if (ls == NULL) {
        return NGX_ERROR;
    }

    *ls = *lss;

    /* Disable unix socket client address extraction
     * from accept call
     * Nginx generates bad addr_text with this enabled */
    ls->addr_ntop = 0;

    ls->socklen = sizeof(struct sockaddr_un);
    saun = ngx_pcalloc(cycle->pool, ls->socklen);
    ls->sockaddr = (struct sockaddr *) saun;
    if (ls->sockaddr == NULL) {
        return NGX_ERROR;
    }
    saun->sun_family = AF_UNIX;
    *ngx_snprintf((u_char *) saun->sun_path, sizeof(saun->sun_path),
                  "%V/" NGX_RTMP_AUTO_PUSH_SOCKNAME ".%i",
                  &apcf->socket_dir, ngx_process_slot)
        = 0;

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, cycle->log, 0,
                   "auto_push: create socket '%s'",
                   saun->sun_path);

    if (ngx_file_info(saun->sun_path, &fi) != ENOENT) {
        ngx_log_debug1(NGX_LOG_DEBUG_RTMP, cycle->log, 0,
                       "auto_push: delete existing socket '%s'",
                       saun->sun_path);
        ngx_delete_file(saun->sun_path);
    }

    ngx_str_set(&ls->addr_text, "worker_socket");

    s = ngx_socket(AF_UNIX, SOCK_STREAM, 0);
    if (s == -1) {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_socket_errno,
                      ngx_socket_n " worker_socket failed");
        return NGX_ERROR;
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
                   (const void *) &reuseaddr, sizeof(int))
        == -1)
    {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_socket_errno,
                "setsockopt(SO_REUSEADDR) worker_socket failed");
        goto sock_error;
    }

    if (!(ngx_event_flags & NGX_USE_AIO_EVENT)) {
        if (ngx_nonblocking(s) == -1) {
            ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_socket_errno,
                          ngx_nonblocking_n " worker_socket failed");
            return NGX_ERROR;
        }
    }

    if (bind(s, (struct sockaddr *) saun, sizeof(*saun)) == -1) {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_socket_errno,
                      ngx_nonblocking_n " worker_socket bind failed");
        goto sock_error;
    }

    if (listen(s, NGX_LISTEN_BACKLOG) == -1) {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_socket_errno,
                      "listen() to worker_socket, backlog %d failed",
                      NGX_LISTEN_BACKLOG);
        goto sock_error;
    }

    ls->fd = s;
    ls->listen = 1;

    return NGX_OK;

sock_error:
    if (s != (ngx_socket_t) -1 && ngx_close_socket(s) == -1) {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_socket_errno,
                ngx_close_socket_n " worker_socket failed");
    }
    ngx_delete_file(saun->sun_path);

    return NGX_ERROR;

#else  /* NGX_HAVE_UNIX_DOMAIN */

    return NGX_OK;

#endif /* NGX_HAVE_UNIX_DOMAIN */
}