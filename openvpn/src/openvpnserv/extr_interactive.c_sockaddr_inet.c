#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sa_inet ;
struct TYPE_10__ {int /*<<< orphan*/  ipv6; int /*<<< orphan*/  ipv4; } ;
typedef  TYPE_3__ inet_address_t ;
struct TYPE_9__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_11__ {short si_family; TYPE_2__ Ipv6; TYPE_1__ Ipv4; } ;
typedef  TYPE_4__ SOCKADDR_INET ;

/* Variables and functions */
 short AF_INET ; 
 short AF_INET6 ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_4__*,int) ; 

__attribute__((used)) static SOCKADDR_INET
sockaddr_inet(short family, inet_address_t *addr)
{
    SOCKADDR_INET sa_inet;
    ZeroMemory(&sa_inet, sizeof(sa_inet));
    sa_inet.si_family = family;
    if (family == AF_INET)
    {
        sa_inet.Ipv4.sin_addr = addr->ipv4;
    }
    else if (family == AF_INET6)
    {
        sa_inet.Ipv6.sin6_addr = addr->ipv6;
    }
    return sa_inet;
}