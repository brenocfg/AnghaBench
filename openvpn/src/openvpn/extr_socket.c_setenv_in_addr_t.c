#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_6__ {TYPE_2__ in4; } ;
struct openvpn_sockaddr {TYPE_3__ addr; } ;
struct env_set {int dummy; } ;
typedef  scalar_t__ in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  CLEAR (struct openvpn_sockaddr) ; 
 unsigned int const SA_SET_IF_NONZERO ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  setenv_sockaddr (struct env_set*,char const*,struct openvpn_sockaddr*,unsigned int const) ; 

void
setenv_in_addr_t(struct env_set *es, const char *name_prefix, in_addr_t addr, const unsigned int flags)
{
    if (addr || !(flags & SA_SET_IF_NONZERO))
    {
        struct openvpn_sockaddr si;
        CLEAR(si);
        si.addr.in4.sin_family = AF_INET;
        si.addr.in4.sin_addr.s_addr = htonl(addr);
        setenv_sockaddr(es, name_prefix, &si, flags);
    }
}