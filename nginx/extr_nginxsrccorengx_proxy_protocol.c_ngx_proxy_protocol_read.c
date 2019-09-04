#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int /*<<< orphan*/  signature ;
typedef  int /*<<< orphan*/  ngx_proxy_protocol_header_t ;
typedef  int ngx_int_t ;
struct TYPE_6__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int /*<<< orphan*/  log; scalar_t__ proxy_protocol_port; TYPE_4__ proxy_protocol_addr; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_connection_t ;
typedef  scalar_t__ in_port_t ;

/* Variables and functions */
 char CR ; 
 char LF ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int ngx_atoi (char*,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 char* ngx_proxy_protocol_v2_read (TYPE_1__*,char*,char*) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 

u_char *
ngx_proxy_protocol_read(ngx_connection_t *c, u_char *buf, u_char *last)
{
    size_t     len;
    u_char     ch, *p, *addr, *port;
    ngx_int_t  n;

    static const u_char signature[] = "\r\n\r\n\0\r\nQUIT\n";

    p = buf;
    len = last - buf;

    if (len >= sizeof(ngx_proxy_protocol_header_t)
        && memcmp(p, signature, sizeof(signature) - 1) == 0)
    {
        return ngx_proxy_protocol_v2_read(c, buf, last);
    }

    if (len < 8 || ngx_strncmp(p, "PROXY ", 6) != 0) {
        goto invalid;
    }

    p += 6;
    len -= 6;

    if (len >= 7 && ngx_strncmp(p, "UNKNOWN", 7) == 0) {
        ngx_log_debug0(NGX_LOG_DEBUG_CORE, c->log, 0,
                       "PROXY protocol unknown protocol");
        p += 7;
        goto skip;
    }

    if (len < 5 || ngx_strncmp(p, "TCP", 3) != 0
        || (p[3] != '4' && p[3] != '6') || p[4] != ' ')
    {
        goto invalid;
    }

    p += 5;
    addr = p;

    for ( ;; ) {
        if (p == last) {
            goto invalid;
        }

        ch = *p++;

        if (ch == ' ') {
            break;
        }

        if (ch != ':' && ch != '.'
            && (ch < 'a' || ch > 'f')
            && (ch < 'A' || ch > 'F')
            && (ch < '0' || ch > '9'))
        {
            goto invalid;
        }
    }

    len = p - addr - 1;
    c->proxy_protocol_addr.data = ngx_pnalloc(c->pool, len);

    if (c->proxy_protocol_addr.data == NULL) {
        return NULL;
    }

    ngx_memcpy(c->proxy_protocol_addr.data, addr, len);
    c->proxy_protocol_addr.len = len;

    for ( ;; ) {
        if (p == last) {
            goto invalid;
        }

        if (*p++ == ' ') {
            break;
        }
    }

    port = p;

    for ( ;; ) {
        if (p == last) {
            goto invalid;
        }

        if (*p++ == ' ') {
            break;
        }
    }

    len = p - port - 1;

    n = ngx_atoi(port, len);

    if (n < 0 || n > 65535) {
        goto invalid;
    }

    c->proxy_protocol_port = (in_port_t) n;

    ngx_log_debug2(NGX_LOG_DEBUG_CORE, c->log, 0,
                   "PROXY protocol address: %V %d", &c->proxy_protocol_addr,
                   c->proxy_protocol_port);

skip:

    for ( /* void */ ; p < last - 1; p++) {
        if (p[0] == CR && p[1] == LF) {
            return p + 2;
        }
    }

invalid:

    ngx_log_error(NGX_LOG_ERR, c->log, 0,
                  "broken header: \"%*s\"", (size_t) (last - buf), buf);

    return NULL;
}