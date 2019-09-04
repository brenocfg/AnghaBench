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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ftp_result_t ;
typedef  int /*<<< orphan*/  _i32 ;
struct TYPE_3__ {int uservalid; int passvalid; } ;
struct TYPE_4__ {int state; scalar_t__ lc_sd; scalar_t__ c_sd; int substate; scalar_t__ d_sd; int special_file; scalar_t__ ld_sd; int /*<<< orphan*/  dtimeout; scalar_t__ dBuffer; int /*<<< orphan*/  ctimeout; TYPE_1__ loggin; int /*<<< orphan*/  logginRetries; int /*<<< orphan*/  txRetries; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_FTP_RESULT_CONTINUE ; 
 int /*<<< orphan*/  E_FTP_RESULT_FAILED ; 
 int /*<<< orphan*/  E_FTP_RESULT_OK ; 
#define  E_FTP_STE_CONTINUE_FILE_RX 137 
#define  E_FTP_STE_CONTINUE_FILE_TX 136 
#define  E_FTP_STE_CONTINUE_LISTING 135 
#define  E_FTP_STE_DISABLED 134 
#define  E_FTP_STE_END_TRANSFER 133 
#define  E_FTP_STE_READY 132 
#define  E_FTP_STE_START 131 
#define  E_FTP_STE_SUB_DATA_CONNECTED 130 
#define  E_FTP_STE_SUB_DISCONNECTED 129 
#define  E_FTP_STE_SUB_LISTEN_FOR_DATA 128 
 int /*<<< orphan*/  FTP_BUFFER_SIZE ; 
 int /*<<< orphan*/  FTP_CMD_CLIENTS_MAX ; 
 int /*<<< orphan*/  FTP_CMD_PORT ; 
 int FTP_CYCLE_TIME_MS ; 
 int FTP_DATA_TIMEOUT_MS ; 
 int /*<<< orphan*/  SOCKETFIFO_IsEmpty () ; 
 int /*<<< orphan*/  ftp_close_files () ; 
 int /*<<< orphan*/  ftp_close_filesystem_on_error () ; 
 int /*<<< orphan*/  ftp_create_listening_socket (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ ftp_data ; 
 int /*<<< orphan*/  ftp_list_dir (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftp_path ; 
 int /*<<< orphan*/  ftp_process_cmd () ; 
 int /*<<< orphan*/  ftp_read_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftp_recv_non_blocking (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftp_send_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftp_send_from_fifo () ; 
 int /*<<< orphan*/  ftp_send_reply (int,char*) ; 
 int /*<<< orphan*/  ftp_wait_for_connection (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ftp_wait_for_enabled () ; 
 int /*<<< orphan*/  ftp_write_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  servers_close_socket (scalar_t__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  updater_finnish () ; 
 int /*<<< orphan*/  updater_write (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_is_connected () ; 

void ftp_run (void) {
    switch (ftp_data.state) {
        case E_FTP_STE_DISABLED:
            ftp_wait_for_enabled();
            break;
        case E_FTP_STE_START:
            if (wlan_is_connected() && ftp_create_listening_socket(&ftp_data.lc_sd, FTP_CMD_PORT, FTP_CMD_CLIENTS_MAX - 1)) {
                ftp_data.state = E_FTP_STE_READY;
            }
            break;
        case E_FTP_STE_READY:
            if (ftp_data.c_sd < 0 && ftp_data.substate == E_FTP_STE_SUB_DISCONNECTED) {
                if (E_FTP_RESULT_OK == ftp_wait_for_connection(ftp_data.lc_sd, &ftp_data.c_sd)) {
                    ftp_data.txRetries = 0;
                    ftp_data.logginRetries = 0;
                    ftp_data.ctimeout = 0;
                    ftp_data.loggin.uservalid = false;
                    ftp_data.loggin.passvalid = false;
                    strcpy (ftp_path, "/");
                    ftp_send_reply (220, "MicroPython FTP Server");
                    break;
                }
            }
            if (SOCKETFIFO_IsEmpty()) {
                if (ftp_data.c_sd > 0 && ftp_data.substate != E_FTP_STE_SUB_LISTEN_FOR_DATA) {
                    ftp_process_cmd();
                    if (ftp_data.state != E_FTP_STE_READY) {
                        break;
                    }
                }
            }
            break;
        case E_FTP_STE_END_TRANSFER:
            break;
        case E_FTP_STE_CONTINUE_LISTING:
            // go on with listing only if the transmit buffer is empty
            if (SOCKETFIFO_IsEmpty()) {
                uint32_t listsize;
                ftp_list_dir((char *)ftp_data.dBuffer, FTP_BUFFER_SIZE, &listsize);
                if (listsize > 0) {
                    ftp_send_data(listsize);
                } else {
                    ftp_send_reply(226, NULL);
                    ftp_data.state = E_FTP_STE_END_TRANSFER;
                }
                ftp_data.ctimeout = 0;
            }
            break;
        case E_FTP_STE_CONTINUE_FILE_TX:
            // read the next block from the file only if the previous one has been sent
            if (SOCKETFIFO_IsEmpty()) {
                uint32_t readsize;
                ftp_result_t result;
                ftp_data.ctimeout = 0;
                result = ftp_read_file ((char *)ftp_data.dBuffer, FTP_BUFFER_SIZE, &readsize);
                if (result == E_FTP_RESULT_FAILED) {
                    ftp_send_reply(451, NULL);
                    ftp_data.state = E_FTP_STE_END_TRANSFER;
                }
                else {
                    if (readsize > 0) {
                        ftp_send_data(readsize);
                    }
                    if (result == E_FTP_RESULT_OK) {
                        ftp_send_reply(226, NULL);
                        ftp_data.state = E_FTP_STE_END_TRANSFER;
                    }
                }
            }
            break;
        case E_FTP_STE_CONTINUE_FILE_RX:
            if (SOCKETFIFO_IsEmpty()) {
                _i32 len;
                ftp_result_t result;
                if (E_FTP_RESULT_OK == (result = ftp_recv_non_blocking(ftp_data.d_sd, ftp_data.dBuffer, FTP_BUFFER_SIZE, &len))) {
                    ftp_data.dtimeout = 0;
                    ftp_data.ctimeout = 0;
                    // its a software update
                    if (ftp_data.special_file) {
                        if (updater_write(ftp_data.dBuffer, len)) {
                            break;
                        }
                    }
                    // user file being received
                    else if (E_FTP_RESULT_OK == ftp_write_file ((char *)ftp_data.dBuffer, len)) {
                        break;
                    }
                    ftp_send_reply(451, NULL);
                    ftp_data.state = E_FTP_STE_END_TRANSFER;
                }
                else if (result == E_FTP_RESULT_CONTINUE) {
                    if (ftp_data.dtimeout++ > FTP_DATA_TIMEOUT_MS / FTP_CYCLE_TIME_MS) {
                        ftp_close_files();
                        ftp_send_reply(426, NULL);
                        ftp_data.state = E_FTP_STE_END_TRANSFER;
                    }
                }
                else {
                    if (ftp_data.special_file) {
                        ftp_data.special_file = false;
                        updater_finnish();
                    }
                    ftp_close_files();
                    ftp_send_reply(226, NULL);
                    ftp_data.state = E_FTP_STE_END_TRANSFER;
                }
            }
            break;
        default:
            break;
    }

    switch (ftp_data.substate) {
    case E_FTP_STE_SUB_DISCONNECTED:
        break;
    case E_FTP_STE_SUB_LISTEN_FOR_DATA:
        if (E_FTP_RESULT_OK == ftp_wait_for_connection(ftp_data.ld_sd, &ftp_data.d_sd)) {
            ftp_data.dtimeout = 0;
            ftp_data.substate = E_FTP_STE_SUB_DATA_CONNECTED;
        }
        else if (ftp_data.dtimeout++ > FTP_DATA_TIMEOUT_MS / FTP_CYCLE_TIME_MS) {
            ftp_data.dtimeout = 0;
            // close the listening socket
            servers_close_socket(&ftp_data.ld_sd);
            ftp_data.substate = E_FTP_STE_SUB_DISCONNECTED;
        }
        break;
    case E_FTP_STE_SUB_DATA_CONNECTED:
        if (ftp_data.state == E_FTP_STE_READY && ftp_data.dtimeout++ > FTP_DATA_TIMEOUT_MS / FTP_CYCLE_TIME_MS) {
            // close the listening and the data socket
            servers_close_socket(&ftp_data.ld_sd);
            servers_close_socket(&ftp_data.d_sd);
            ftp_close_filesystem_on_error ();
            ftp_data.substate = E_FTP_STE_SUB_DISCONNECTED;
        }
        break;
    default:
        break;
    }

    // send data pending in the queue
    ftp_send_from_fifo();

    // check the state of the data sockets
    if (ftp_data.d_sd < 0 && (ftp_data.state > E_FTP_STE_READY)) {
        ftp_data.substate = E_FTP_STE_SUB_DISCONNECTED;
        ftp_data.state = E_FTP_STE_READY;
    }
}