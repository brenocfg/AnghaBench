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
typedef  int /*<<< orphan*/  u_char ;
typedef  int ngx_uint_t ;
struct TYPE_4__ {int len; scalar_t__ data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  scalar_t__ ngx_err_t ;
typedef  int /*<<< orphan*/  ngx_atomic_uint_t ;

/* Variables and functions */
 scalar_t__ DeleteFile (char const*) ; 
 scalar_t__ MoveFile (char const*,char const*) ; 
 int NGX_ATOMIC_T_LEN ; 
 scalar_t__ NGX_ENOMEM ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/ * ngx_alloc (int,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_errno ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  ngx_next_temp_number (int) ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

ngx_err_t
ngx_win32_rename_file(ngx_str_t *from, ngx_str_t *to, ngx_log_t *log)
{
    u_char             *name;
    ngx_err_t           err;
    ngx_uint_t          collision;
    ngx_atomic_uint_t   num;

    name = ngx_alloc(to->len + 1 + NGX_ATOMIC_T_LEN + 1 + sizeof("DELETE"),
                     log);
    if (name == NULL) {
        return NGX_ENOMEM;
    }

    ngx_memcpy(name, to->data, to->len);

    collision = 0;

    /* mutex_lock() (per cache or single ?) */

    for ( ;; ) {
        num = ngx_next_temp_number(collision);

        ngx_sprintf(name + to->len, ".%0muA.DELETE%Z", num);

        if (MoveFile((const char *) to->data, (const char *) name) != 0) {
            break;
        }

        collision = 1;

        ngx_log_error(NGX_LOG_CRIT, log, ngx_errno,
                      "MoveFile() \"%s\" to \"%s\" failed", to->data, name);
    }

    if (MoveFile((const char *) from->data, (const char *) to->data) == 0) {
        err = ngx_errno;

    } else {
        err = 0;
    }

    if (DeleteFile((const char *) name) == 0) {
        ngx_log_error(NGX_LOG_CRIT, log, ngx_errno,
                      "DeleteFile() \"%s\" failed", name);
    }

    /* mutex_unlock() */

    ngx_free(name);

    return err;
}