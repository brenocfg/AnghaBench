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
typedef  int /*<<< orphan*/  u_char ;
typedef  int ngx_uint_t ;

/* Variables and functions */

__attribute__((used)) static u_char *
ngx_http_v2_write_int(u_char *pos, ngx_uint_t prefix, ngx_uint_t value)
{
    if (value < prefix) {
        *pos++ |= value;
        return pos;
    }

    *pos++ |= prefix;
    value -= prefix;

    while (value >= 128) {
        *pos++ = value % 128 + 128;
        value /= 128;
    }

    *pos++ = (u_char) value;

    return pos;
}