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
struct TYPE_3__ {char* data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_test_full_name(ngx_str_t *name)
{
#if (NGX_WIN32)
    u_char  c0, c1;

    c0 = name->data[0];

    if (name->len < 2) {
        if (c0 == '/') {
            return 2;
        }

        return NGX_DECLINED;
    }

    c1 = name->data[1];

    if (c1 == ':') {
        c0 |= 0x20;

        if ((c0 >= 'a' && c0 <= 'z')) {
            return NGX_OK;
        }

        return NGX_DECLINED;
    }

    if (c1 == '/') {
        return NGX_OK;
    }

    if (c0 == '/') {
        return 2;
    }

    return NGX_DECLINED;

#else

    if (name->data[0] == '/') {
        return NGX_OK;
    }

    return NGX_DECLINED;

#endif
}