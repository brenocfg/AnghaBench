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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_3__ {scalar_t__ last; scalar_t__ end; } ;
typedef  TYPE_1__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_cpymem (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_box(ngx_buf_t *b, const char box[4])
{
    if (b->last + 4 > b->end) {
        return NGX_ERROR;
    }

    b->last = ngx_cpymem(b->last, (u_char *) box, 4);

    return NGX_OK;
}