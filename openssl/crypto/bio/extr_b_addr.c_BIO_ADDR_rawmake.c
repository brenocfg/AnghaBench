#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_5__ {int sun_family; int sin_family; unsigned short sin_port; int sin6_family; unsigned short sin6_port; struct in6_addr sin6_addr; struct in_addr sin_addr; int /*<<< orphan*/  sun_path; } ;
struct TYPE_4__ {TYPE_2__ s_in6; TYPE_2__ s_in; TYPE_2__ s_un; } ;
typedef  TYPE_1__ BIO_ADDR ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNIX ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,void const*,int) ; 

int BIO_ADDR_rawmake(BIO_ADDR *ap, int family,
                     const void *where, size_t wherelen,
                     unsigned short port)
{
#ifdef AF_UNIX
    if (family == AF_UNIX) {
        if (wherelen + 1 > sizeof(ap->s_un.sun_path))
            return 0;
        memset(&ap->s_un, 0, sizeof(ap->s_un));
        ap->s_un.sun_family = family;
        strncpy(ap->s_un.sun_path, where, sizeof(ap->s_un.sun_path) - 1);
        return 1;
    }
#endif
    if (family == AF_INET) {
        if (wherelen != sizeof(struct in_addr))
            return 0;
        memset(&ap->s_in, 0, sizeof(ap->s_in));
        ap->s_in.sin_family = family;
        ap->s_in.sin_port = port;
        ap->s_in.sin_addr = *(struct in_addr *)where;
        return 1;
    }
#ifdef AF_INET6
    if (family == AF_INET6) {
        if (wherelen != sizeof(struct in6_addr))
            return 0;
        memset(&ap->s_in6, 0, sizeof(ap->s_in6));
        ap->s_in6.sin6_family = family;
        ap->s_in6.sin6_port = port;
        ap->s_in6.sin6_addr = *(struct in6_addr *)where;
        return 1;
    }
#endif

    return 0;
}