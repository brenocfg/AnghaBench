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
typedef  int /*<<< orphan*/  _u32 ;
struct TYPE_5__ {int /*<<< orphan*/  d_sd; int /*<<< orphan*/  dBuffer; } ;
struct TYPE_4__ {int freedata; int /*<<< orphan*/  closesockets; int /*<<< orphan*/ * sd; int /*<<< orphan*/  datasize; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ SocketFifoElement_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_FTP_CLOSE_NONE ; 
 int /*<<< orphan*/  SOCKETFIFO_Push (TYPE_1__*) ; 
 TYPE_2__ ftp_data ; 

__attribute__((used)) static void ftp_send_data (_u32 datasize) {
    SocketFifoElement_t fifoelement;

    fifoelement.data = ftp_data.dBuffer;
    fifoelement.datasize = datasize;
    fifoelement.sd = &ftp_data.d_sd;
    fifoelement.closesockets = E_FTP_CLOSE_NONE;
    fifoelement.freedata = false;
    SOCKETFIFO_Push (&fifoelement);
}