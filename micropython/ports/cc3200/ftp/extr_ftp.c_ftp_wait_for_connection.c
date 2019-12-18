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
typedef  int /*<<< orphan*/  ftp_result_t ;
typedef  scalar_t__ _i16 ;
typedef  int /*<<< orphan*/  SlSocklen_t ;
typedef  int /*<<< orphan*/  SlSockAddr_t ;
typedef  int /*<<< orphan*/  SlSockAddrIn_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_FTP_RESULT_CONTINUE ; 
 int /*<<< orphan*/  E_FTP_RESULT_FAILED ; 
 int /*<<< orphan*/  E_FTP_RESULT_OK ; 
 scalar_t__ SL_EAGAIN ; 
 int /*<<< orphan*/  ftp_reset () ; 
 int /*<<< orphan*/  modusocket_socket_add (scalar_t__,int) ; 
 scalar_t__ sl_Accept (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ftp_result_t ftp_wait_for_connection (_i16 l_sd, _i16 *n_sd) {
    SlSockAddrIn_t sClientAddress;
    SlSocklen_t  in_addrSize;

    // accepts a connection from a TCP client, if there is any, otherwise returns SL_EAGAIN
    *n_sd = sl_Accept(l_sd, (SlSockAddr_t *)&sClientAddress, (SlSocklen_t *)&in_addrSize);
    _i16 _sd = *n_sd;
    if (_sd == SL_EAGAIN) {
        return E_FTP_RESULT_CONTINUE;
    }
    else if (_sd < 0) {
        // error
        ftp_reset();
        return E_FTP_RESULT_FAILED;
    }

    // add the new socket to the network administration
    modusocket_socket_add(_sd, false);

    // client connected, so go on
    return E_FTP_RESULT_OK;
}