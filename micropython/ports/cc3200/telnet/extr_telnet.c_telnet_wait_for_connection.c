#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  connected; } ;
struct TYPE_4__ {scalar_t__ n_sd; int credentialsValid; scalar_t__ timeout; scalar_t__ logginRetries; TYPE_1__ substate; int /*<<< orphan*/  state; scalar_t__ txRetries; scalar_t__ rxRindex; scalar_t__ rxWindex; int /*<<< orphan*/  sd; } ;
typedef  int /*<<< orphan*/  SlSocklen_t ;
typedef  int /*<<< orphan*/  SlSockAddr_t ;
typedef  int /*<<< orphan*/  SlSockAddrIn_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_TELNET_STE_CONNECTED ; 
 int /*<<< orphan*/  E_TELNET_STE_SUB_WELCOME ; 
 scalar_t__ SL_EAGAIN ; 
 int /*<<< orphan*/  modusocket_socket_add (scalar_t__,int) ; 
 int /*<<< orphan*/  servers_close_socket (int /*<<< orphan*/ *) ; 
 scalar_t__ sl_Accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ telnet_data ; 
 int /*<<< orphan*/  telnet_reset () ; 

__attribute__((used)) static void telnet_wait_for_connection (void) {
    SlSocklen_t  in_addrSize;
    SlSockAddrIn_t sClientAddress;

    // accepts a connection from a TCP client, if there is any, otherwise returns SL_EAGAIN
    telnet_data.n_sd = sl_Accept(telnet_data.sd, (SlSockAddr_t *)&sClientAddress, (SlSocklen_t *)&in_addrSize);
    if (telnet_data.n_sd == SL_EAGAIN) {
        return;
    }
    else {
        if (telnet_data.n_sd <= 0) {
            // error
            telnet_reset();
            return;
        }

        // close the listening socket, we don't need it anymore
        servers_close_socket(&telnet_data.sd);

        // add the new socket to the network administration
        modusocket_socket_add(telnet_data.n_sd, false);

        // client connected, so go on
        telnet_data.rxWindex = 0;
        telnet_data.rxRindex = 0;
        telnet_data.txRetries = 0;

        telnet_data.state = E_TELNET_STE_CONNECTED;
        telnet_data.substate.connected = E_TELNET_STE_SUB_WELCOME;
        telnet_data.credentialsValid = true;
        telnet_data.logginRetries = 0;
        telnet_data.timeout = 0;
    }
}