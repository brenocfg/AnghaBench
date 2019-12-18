#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {TYPE_2__ sin_addr; } ;
struct TYPE_5__ {scalar_t__ sa_family; } ;
struct TYPE_8__ {TYPE_3__ in4; TYPE_1__ sa; } ;
struct openvpn_sockaddr {TYPE_4__ addr; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline in_addr_t
addr_host(const struct openvpn_sockaddr *addr)
{
    /*
     * "public" addr returned is checked against ifconfig for
     * possible clash: non sense for now given
     * that we do ifconfig only IPv4
     */
    if (addr->addr.sa.sa_family != AF_INET)
    {
        return 0;
    }
    return ntohl(addr->addr.in4.sin_addr.s_addr);
}