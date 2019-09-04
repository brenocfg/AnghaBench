#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int _u16 ;
struct TYPE_5__ {int /*<<< orphan*/  c_sd; } ;
struct TYPE_4__ {int freedata; scalar_t__ data; int /*<<< orphan*/  datasize; int /*<<< orphan*/  closesockets; int /*<<< orphan*/ * sd; } ;
typedef  TYPE_1__ SocketFifoElement_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_FTP_CLOSE_CMD_AND_DATA ; 
 int /*<<< orphan*/  E_FTP_CLOSE_DATA ; 
 int /*<<< orphan*/  E_FTP_CLOSE_NONE ; 
 int /*<<< orphan*/  SOCKETFIFO_Push (TYPE_1__*) ; 
 scalar_t__ ftp_cmd_buffer ; 
 TYPE_2__ ftp_data ; 
 int /*<<< orphan*/  mem_Free (scalar_t__) ; 
 scalar_t__ mem_Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void ftp_send_reply (_u16 status, char *message) {
    SocketFifoElement_t fifoelement;
    if (!message) {
        message = "";
    }
    snprintf((char *)ftp_cmd_buffer, 4, "%u", status);
    strcat ((char *)ftp_cmd_buffer, " ");
    strcat ((char *)ftp_cmd_buffer, message);
    strcat ((char *)ftp_cmd_buffer, "\r\n");
    fifoelement.sd = &ftp_data.c_sd;
    fifoelement.datasize = strlen((char *)ftp_cmd_buffer);
    fifoelement.data = mem_Malloc(fifoelement.datasize);
    if (status == 221) {
        fifoelement.closesockets = E_FTP_CLOSE_CMD_AND_DATA;
    }
    else if (status == 426 || status == 451 || status == 550) {
        fifoelement.closesockets = E_FTP_CLOSE_DATA;
    }
    else {
        fifoelement.closesockets = E_FTP_CLOSE_NONE;
    }
    fifoelement.freedata = true;
    if (fifoelement.data) {
        memcpy (fifoelement.data, ftp_cmd_buffer, fifoelement.datasize);
        if (!SOCKETFIFO_Push (&fifoelement)) {
            mem_Free(fifoelement.data);
        }
    }
}