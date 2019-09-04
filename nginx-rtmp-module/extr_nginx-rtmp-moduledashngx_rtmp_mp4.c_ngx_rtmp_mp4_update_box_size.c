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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_4__ {int /*<<< orphan*/ * last; } ;
typedef  TYPE_1__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_32 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_update_box_size(ngx_buf_t *b, u_char *p)
{
    u_char  *curpos;

    if (p == NULL) {
        return NGX_ERROR;
    }

    curpos = b->last;

    b->last = p;

    ngx_rtmp_mp4_field_32(b, (uint32_t) (curpos - p));

    b->last = curpos;

    return NGX_OK;
}