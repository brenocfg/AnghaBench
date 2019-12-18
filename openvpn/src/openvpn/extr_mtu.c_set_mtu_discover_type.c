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
typedef  int sa_family_t ;
typedef  int /*<<< orphan*/  mtu_type ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_MTU_DISCOVER ; 
 int /*<<< orphan*/  IP_MTU_DISCOVER ; 
 int /*<<< orphan*/  MTUDISC_NOT_SUPPORTED_MSG ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

void
set_mtu_discover_type(int sd, int mtu_type, sa_family_t proto_af)
{
    if (mtu_type >= 0)
    {
        switch (proto_af)
        {
#if defined(HAVE_SETSOCKOPT) && defined(IP_MTU_DISCOVER)
            case AF_INET:
                if (setsockopt
                        (sd, IPPROTO_IP, IP_MTU_DISCOVER, &mtu_type, sizeof(mtu_type)))
                {
                    msg(M_ERR, "Error setting IP_MTU_DISCOVER type=%d on TCP/UDP socket",
                        mtu_type);
                }
                break;

#endif
#if defined(HAVE_SETSOCKOPT) && defined(IPV6_MTU_DISCOVER)
            case AF_INET6:
                if (setsockopt
                        (sd, IPPROTO_IPV6, IPV6_MTU_DISCOVER, &mtu_type, sizeof(mtu_type)))
                {
                    msg(M_ERR, "Error setting IPV6_MTU_DISCOVER type=%d on TCP6/UDP6 socket",
                        mtu_type);
                }
                break;

#endif
            default:
                msg(M_FATAL, MTUDISC_NOT_SUPPORTED_MSG);
                break;
        }
    }
}