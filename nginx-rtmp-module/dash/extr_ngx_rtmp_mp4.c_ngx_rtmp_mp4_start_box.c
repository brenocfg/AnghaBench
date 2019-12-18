#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/ * last; } ;
typedef  TYPE_1__ ngx_buf_t ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_rtmp_mp4_box (TYPE_1__*,char const*) ; 
 scalar_t__ ngx_rtmp_mp4_field_32 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_char *
ngx_rtmp_mp4_start_box(ngx_buf_t *b, const char box[4])
{
    u_char  *p;

    p = b->last;

    if (ngx_rtmp_mp4_field_32(b, 0) != NGX_OK) {
        return NULL;
    }

    if (ngx_rtmp_mp4_box(b, box) != NGX_OK) {
        return NULL;
    }

    return p;
}