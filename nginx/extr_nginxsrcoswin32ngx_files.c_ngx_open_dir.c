#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_err_t ;
struct TYPE_6__ {int valid_info; int ready; int /*<<< orphan*/  dir; int /*<<< orphan*/  finddata; } ;
typedef  TYPE_2__ ngx_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  FindFirstFile (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 char* ngx_cpymem (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_free (char*) ; 
 int /*<<< orphan*/  ngx_set_errno (int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_open_dir(ngx_str_t *name, ngx_dir_t *dir)
{
    u_char     *pattern, *p;
    ngx_err_t   err;

    pattern = malloc(name->len + 3);
    if (pattern == NULL) {
        return NGX_ERROR;
    }

    p = ngx_cpymem(pattern, name->data, name->len);

    *p++ = '/';
    *p++ = '*';
    *p = '\0';

    dir->dir = FindFirstFile((const char *) pattern, &dir->finddata);

    if (dir->dir == INVALID_HANDLE_VALUE) {
        err = ngx_errno;
        ngx_free(pattern);
        ngx_set_errno(err);
        return NGX_ERROR;
    }

    ngx_free(pattern);

    dir->valid_info = 1;
    dir->ready = 1;

    return NGX_OK;
}