#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  dst_port; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  dst_port; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_addr; } ;
struct TYPE_12__ {TYPE_4__ ip6; TYPE_3__ ip4; } ;
struct proxy_header_v2 {int cmd_ver; int fam; TYPE_5__ addr; int /*<<< orphan*/  len; } ;
struct lwan_request_parser_helper {TYPE_1__* buffer; } ;
struct lwan_request {int /*<<< orphan*/  flags; struct lwan_proxy* proxy; struct lwan_request_parser_helper* helper; } ;
struct TYPE_14__ {struct sockaddr_in ipv4; struct sockaddr_in6 ipv6; } ;
struct TYPE_13__ {struct sockaddr_in ipv4; struct sockaddr_in6 ipv6; } ;
struct lwan_proxy {TYPE_7__ to; TYPE_6__ from; } ;
struct TYPE_8__ {unsigned int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 scalar_t__ LIKELY (int) ; 
 int /*<<< orphan*/  REQUEST_PROXIED ; 
 scalar_t__ UNLIKELY (int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *parse_proxy_protocol_v2(struct lwan_request *request, char *buffer)
{
    struct proxy_header_v2 *hdr = (struct proxy_header_v2 *)buffer;
    struct lwan_request_parser_helper *helper = request->helper;
    const unsigned int proto_signature_length = 16;
    unsigned int size;
    struct lwan_proxy *const proxy = request->proxy;

    enum { LOCAL = 0x20, PROXY = 0x21, TCP4 = 0x11, TCP6 = 0x21 };

    size = proto_signature_length + (unsigned int)ntohs(hdr->len);
    if (UNLIKELY(size > (unsigned int)sizeof(*hdr)))
        return NULL;
    if (UNLIKELY(size >= helper->buffer->len))
        return NULL;

    if (LIKELY(hdr->cmd_ver == PROXY)) {
        if (hdr->fam == TCP4) {
            struct sockaddr_in *from = &proxy->from.ipv4;
            struct sockaddr_in *to = &proxy->to.ipv4;

            to->sin_family = from->sin_family = AF_INET;

            from->sin_addr.s_addr = hdr->addr.ip4.src_addr;
            from->sin_port = hdr->addr.ip4.src_port;

            to->sin_addr.s_addr = hdr->addr.ip4.dst_addr;
            to->sin_port = hdr->addr.ip4.dst_port;
        } else if (hdr->fam == TCP6) {
            struct sockaddr_in6 *from = &proxy->from.ipv6;
            struct sockaddr_in6 *to = &proxy->to.ipv6;

            from->sin6_family = to->sin6_family = AF_INET6;

            from->sin6_addr = hdr->addr.ip6.src_addr;
            from->sin6_port = hdr->addr.ip6.src_port;

            to->sin6_addr = hdr->addr.ip6.dst_addr;
            to->sin6_port = hdr->addr.ip6.dst_port;
        } else {
            return NULL;
        }
    } else if (hdr->cmd_ver == LOCAL) {
        struct sockaddr_in *from = &proxy->from.ipv4;
        struct sockaddr_in *to = &proxy->to.ipv4;

        from->sin_family = to->sin_family = AF_UNSPEC;
    } else {
        return NULL;
    }

    request->flags |= REQUEST_PROXIED;
    return buffer + size;
}