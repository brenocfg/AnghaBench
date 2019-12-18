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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_3__ {scalar_t__ end; int /*<<< orphan*/  last; } ;
typedef  TYPE_1__ ngx_buf_t ;
typedef  int /*<<< orphan*/  bytes ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_cpymem (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_field_16(ngx_buf_t *b, uint16_t n)
{
    u_char  bytes[2];

    bytes[0] = ((uint32_t) n >> 8) & 0xFF;
    bytes[1] = (uint32_t) n & 0xFF;

    if (b->last + sizeof(bytes) > b->end) {
        return NGX_ERROR;
    }

    b->last = ngx_cpymem(b->last, bytes, sizeof(bytes));

    return NGX_OK;
}