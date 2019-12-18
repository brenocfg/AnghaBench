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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_parse_descr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_rtmp_r16 (scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_parse_es(ngx_rtmp_session_t *s, u_char *pos, u_char *last)
{
    uint16_t    id;
    uint8_t     flags;

    if (pos + 3 > last) {
        return NGX_ERROR;
    }

    id = ngx_rtmp_r16(*(uint16_t *) pos);
    pos += 2;

    flags = *(uint8_t *) pos;
    ++pos;

    if (flags & 0x80) { /* streamDependenceFlag */
        pos += 2;
    }

    if (flags & 0x40) { /* URL_FLag */
        return NGX_OK;
    }

    if (flags & 0x20) { /* OCRstreamFlag */
        pos += 2;
    }

    if (pos > last) {
        return NGX_ERROR;
    }

    (void) id;

    ngx_log_debug2(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "mp4: es descriptor es id=%i flags=%i",
                   (ngx_int_t) id, (ngx_int_t) flags);

    return ngx_rtmp_mp4_parse_descr(s, pos, last);
}