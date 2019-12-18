#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  ngx_socket_t ;
typedef  int /*<<< orphan*/  ngx_err_t ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;
struct TYPE_7__ {size_t fd_count; int /*<<< orphan*/ * fd_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TYPE ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 TYPE_3__ master_read_fd_set ; 
 TYPE_3__ master_write_fd_set ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 

__attribute__((used)) static void
ngx_select_repair_fd_sets(ngx_cycle_t *cycle)
{
    int           n;
    u_int         i;
    socklen_t     len;
    ngx_err_t     err;
    ngx_socket_t  s;

    for (i = 0; i < master_read_fd_set.fd_count; i++) {

        s = master_read_fd_set.fd_array[i];
        len = sizeof(int);

        if (getsockopt(s, SOL_SOCKET, SO_TYPE, (char *) &n, &len) == -1) {
            err = ngx_socket_errno;

            ngx_log_error(NGX_LOG_ALERT, cycle->log, err,
                          "invalid descriptor #%d in read fd_set", s);

            FD_CLR(s, &master_read_fd_set);
        }
    }

    for (i = 0; i < master_write_fd_set.fd_count; i++) {

        s = master_write_fd_set.fd_array[i];
        len = sizeof(int);

        if (getsockopt(s, SOL_SOCKET, SO_TYPE, (char *) &n, &len) == -1) {
            err = ngx_socket_errno;

            ngx_log_error(NGX_LOG_ALERT, cycle->log, err,
                          "invalid descriptor #%d in write fd_set", s);

            FD_CLR(s, &master_write_fd_set);
        }
    }
}