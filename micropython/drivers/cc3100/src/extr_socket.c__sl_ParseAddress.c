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
struct TYPE_25__ {int /*<<< orphan*/  _S6_u32; } ;
struct TYPE_26__ {TYPE_6__ _S6_un; } ;
struct TYPE_28__ {TYPE_7__ sin6_addr; } ;
typedef  TYPE_9__ sockaddr_in6 ;
struct TYPE_27__ {int /*<<< orphan*/  address; } ;
struct TYPE_24__ {int /*<<< orphan*/  address; } ;
struct TYPE_21__ {scalar_t__ family; int /*<<< orphan*/  address; int /*<<< orphan*/  port; } ;
struct TYPE_16__ {TYPE_8__ IpV6; TYPE_5__ IpV6EUI48; TYPE_2__ IpV4; } ;
typedef  TYPE_10__ _SocketAddrResponse_u ;
struct TYPE_22__ {int /*<<< orphan*/  _S6_u8; } ;
struct TYPE_23__ {TYPE_3__ _S6_un; } ;
struct TYPE_20__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_19__ {TYPE_4__ sin6_addr; } ;
struct TYPE_18__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct TYPE_17__ {scalar_t__ sa_family; } ;
typedef  int SlSocklen_t ;
typedef  TYPE_11__ SlSockAddr_t ;
typedef  TYPE_12__ SlSockAddrIn_t ;
typedef  TYPE_13__ SlSockAddrIn6_t ;

/* Variables and functions */
 scalar_t__ SL_AF_INET ; 
 scalar_t__ SL_AF_INET6_EUI_48 ; 
 int /*<<< orphan*/  sl_Memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void _sl_ParseAddress(_SocketAddrResponse_u    *pRsp, SlSockAddr_t *addr, SlSocklen_t *addrlen)
{
    /*  Note: parsing of family and port in the generic way for all IPV4, IPV6 and EUI48 */
    /*  is possible as long as these parameters are in the same offset and size for these */
    /*  three families. */
    addr->sa_family                 = pRsp->IpV4.family;
    ((SlSockAddrIn_t *)addr)->sin_port = pRsp->IpV4.port;

    *addrlen = (SL_AF_INET == addr->sa_family) ? sizeof(SlSockAddrIn_t) : sizeof(SlSockAddrIn6_t);

    if(SL_AF_INET == addr->sa_family)
    {
        ((SlSockAddrIn_t *)addr)->sin_addr.s_addr  = pRsp->IpV4.address;
    }
    else if (SL_AF_INET6_EUI_48 == addr->sa_family )
    {
        sl_Memcpy(((SlSockAddrIn6_t *)addr)->sin6_addr._S6_un._S6_u8, pRsp->IpV6EUI48.address, 6);
    }
#ifdef SL_SUPPORT_IPV6
    else
    {
        sl_Memcpy(((sockaddr_in6 *)addr)->sin6_addr._S6_un._S6_u32, pRsp->IpV6.address, 16);
    }
#endif
}