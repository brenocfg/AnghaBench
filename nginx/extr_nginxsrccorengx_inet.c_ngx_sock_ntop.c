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
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  ngx_uint_t ;

/* Variables and functions */
#define  AF_INET 128 
 int /*<<< orphan*/ * ngx_snprintf (int /*<<< orphan*/ *,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

size_t
ngx_sock_ntop(struct sockaddr *sa, socklen_t socklen, u_char *text, size_t len,
    ngx_uint_t port)
{
    u_char               *p;
#if (NGX_HAVE_INET6 || NGX_HAVE_UNIX_DOMAIN)
    size_t                n;
#endif
    struct sockaddr_in   *sin;
#if (NGX_HAVE_INET6)
    struct sockaddr_in6  *sin6;
#endif
#if (NGX_HAVE_UNIX_DOMAIN)
    struct sockaddr_un   *saun;
#endif

    switch (sa->sa_family) {

    case AF_INET:

        sin = (struct sockaddr_in *) sa;
        p = (u_char *) &sin->sin_addr;

        if (port) {
            p = ngx_snprintf(text, len, "%ud.%ud.%ud.%ud:%d",
                             p[0], p[1], p[2], p[3], ntohs(sin->sin_port));
        } else {
            p = ngx_snprintf(text, len, "%ud.%ud.%ud.%ud",
                             p[0], p[1], p[2], p[3]);
        }

        return (p - text);

#if (NGX_HAVE_INET6)

    case AF_INET6:

        sin6 = (struct sockaddr_in6 *) sa;

        n = 0;

        if (port) {
            text[n++] = '[';
        }

        n = ngx_inet6_ntop(sin6->sin6_addr.s6_addr, &text[n], len);

        if (port) {
            n = ngx_sprintf(&text[1 + n], "]:%d",
                            ntohs(sin6->sin6_port)) - text;
        }

        return n;
#endif

#if (NGX_HAVE_UNIX_DOMAIN)

    case AF_UNIX:
        saun = (struct sockaddr_un *) sa;

        /* on Linux sockaddr might not include sun_path at all */

        if (socklen <= (socklen_t) offsetof(struct sockaddr_un, sun_path)) {
            p = ngx_snprintf(text, len, "unix:%Z");

        } else {
            n = ngx_strnlen((u_char *) saun->sun_path,
                            socklen - offsetof(struct sockaddr_un, sun_path));
            p = ngx_snprintf(text, len, "unix:%*s%Z", n, saun->sun_path);
        }

        /* we do not include trailing zero in address length */

        return (p - text - 1);

#endif

    default:
        return 0;
    }
}