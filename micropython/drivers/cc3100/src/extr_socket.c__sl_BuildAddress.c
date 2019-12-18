#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  _S6_u32; } ;
struct TYPE_27__ {TYPE_7__ _S6_un; } ;
struct TYPE_28__ {TYPE_8__ sin6_addr; } ;
typedef  TYPE_9__ sockaddr_in6 ;
struct TYPE_25__ {int /*<<< orphan*/  address; } ;
struct TYPE_22__ {int /*<<< orphan*/  address; } ;
struct TYPE_20__ {int FamilyAndFlags; int /*<<< orphan*/  address; int /*<<< orphan*/  port; } ;
struct TYPE_16__ {TYPE_6__ IpV6; TYPE_3__ IpV6EUI48; TYPE_1__ IpV4; } ;
typedef  TYPE_10__ _SocketAddrCommand_u ;
struct TYPE_23__ {int /*<<< orphan*/  _S6_u8; } ;
struct TYPE_24__ {TYPE_4__ _S6_un; } ;
struct TYPE_21__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_19__ {TYPE_5__ sin6_addr; } ;
struct TYPE_18__ {TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct TYPE_17__ {int sa_family; } ;
typedef  TYPE_11__ SlSockAddr_t ;
typedef  TYPE_12__ SlSockAddrIn_t ;
typedef  TYPE_13__ SlSockAddrIn6_t ;

/* Variables and functions */
 int SL_AF_INET ; 
 int SL_AF_INET6_EUI_48 ; 
 int /*<<< orphan*/  sl_Memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void _sl_BuildAddress(const SlSockAddr_t *addr, _SocketAddrCommand_u    *pCmd)
{

    /* Note: parsing of family and port in the generic way for all IPV4, IPV6 and EUI48
           is possible as long as these parameters are in the same offset and size for these
           three families. */
    pCmd->IpV4.FamilyAndFlags = (addr->sa_family << 4) & 0xF0;
    pCmd->IpV4.port = ((SlSockAddrIn_t *)addr)->sin_port;

    if(SL_AF_INET == addr->sa_family)
    {
        pCmd->IpV4.address  = ((SlSockAddrIn_t *)addr)->sin_addr.s_addr;
    }
    else if (SL_AF_INET6_EUI_48 == addr->sa_family )
    {
        sl_Memcpy( pCmd->IpV6EUI48.address,((SlSockAddrIn6_t *)addr)->sin6_addr._S6_un._S6_u8, 6);
    }
#ifdef SL_SUPPORT_IPV6
    else
    {
        sl_Memcpy(pCmd->IpV6.address, ((sockaddr_in6 *)addr)->sin6_addr._S6_un._S6_u32, 16 );
    }
#endif
}