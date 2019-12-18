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
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  inet_ntop (int,void*,char*,int) ; 
 int /*<<< orphan*/ * strdupAW (char*) ; 

__attribute__((used)) static WCHAR *addr_to_str( struct sockaddr_storage *addr )
{
    char buf[INET6_ADDRSTRLEN];
    void *src;

    switch (addr->ss_family)
    {
    case AF_INET:
        src = &((struct sockaddr_in *)addr)->sin_addr;
        break;
    case AF_INET6:
        src = &((struct sockaddr_in6 *)addr)->sin6_addr;
        break;
    default:
        WARN("unsupported address family %d\n", addr->ss_family);
        return NULL;
    }
    if (!inet_ntop( addr->ss_family, src, buf, sizeof(buf) )) return NULL;
    return strdupAW( buf );
}