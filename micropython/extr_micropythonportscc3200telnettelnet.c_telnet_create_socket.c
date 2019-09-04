#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sServerAddress ;
typedef  int /*<<< orphan*/  nonBlockingOption ;
typedef  int _i16 ;
struct TYPE_9__ {scalar_t__ sd; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_7__ {int NonblockingEnabled; } ;
typedef  TYPE_2__ SlSockNonblocking_t ;
typedef  int /*<<< orphan*/  SlSockAddr_t ;
typedef  TYPE_3__ SlSockAddrIn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SL_AF_INET ; 
 int /*<<< orphan*/  SL_INADDR_ANY ; 
 int /*<<< orphan*/  SL_IPPROTO_TCP ; 
 int /*<<< orphan*/  SL_SOCK_STREAM ; 
 int SL_SOC_OK ; 
 int /*<<< orphan*/  SL_SOL_SOCKET ; 
 int /*<<< orphan*/  SL_SO_NONBLOCKING ; 
 int /*<<< orphan*/  TELNET_MAX_CLIENTS ; 
 int /*<<< orphan*/  TELNET_PORT ; 
 int /*<<< orphan*/  modusocket_socket_add (scalar_t__,int) ; 
 int /*<<< orphan*/  servers_close_socket (scalar_t__*) ; 
 int sl_Bind (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sl_Htons (int /*<<< orphan*/ ) ; 
 int sl_Listen (scalar_t__,int /*<<< orphan*/ ) ; 
 int sl_SetSockOpt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 scalar_t__ sl_Socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ telnet_data ; 

__attribute__((used)) static bool telnet_create_socket (void) {
    SlSockNonblocking_t nonBlockingOption;
    SlSockAddrIn_t sServerAddress;
    _i16 result;

    // Open a socket for telnet
    ASSERT ((telnet_data.sd = sl_Socket(SL_AF_INET, SL_SOCK_STREAM, SL_IPPROTO_TCP)) > 0);
    if (telnet_data.sd > 0) {
        // add the socket to the network administration
        modusocket_socket_add(telnet_data.sd, false);

        // Enable non-blocking mode
        nonBlockingOption.NonblockingEnabled = 1;
        ASSERT ((result = sl_SetSockOpt(telnet_data.sd, SL_SOL_SOCKET, SL_SO_NONBLOCKING, &nonBlockingOption, sizeof(nonBlockingOption))) == SL_SOC_OK);

        // Bind the socket to a port number
        sServerAddress.sin_family = SL_AF_INET;
        sServerAddress.sin_addr.s_addr = SL_INADDR_ANY;
        sServerAddress.sin_port = sl_Htons(TELNET_PORT);

        ASSERT ((result |= sl_Bind(telnet_data.sd, (const SlSockAddr_t *)&sServerAddress, sizeof(sServerAddress))) == SL_SOC_OK);

        // Start listening
        ASSERT ((result |= sl_Listen (telnet_data.sd, TELNET_MAX_CLIENTS)) == SL_SOC_OK);

        if (result == SL_SOC_OK) {
            return true;
        }
        servers_close_socket(&telnet_data.sd);
    }

    return false;
}