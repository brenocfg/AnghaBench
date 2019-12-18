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
struct TYPE_3__ {scalar_t__* pReadPos; scalar_t__* pRcvMsgBuff; scalar_t__* pWritePos; } ;
struct TYPE_4__ {TYPE_1__ rcv_buff; } ;
typedef  TYPE_1__ RcvMsgBuff ;

/* Variables and functions */
 int /*<<< orphan*/  ETS_INTR_LOCK () ; 
 int /*<<< orphan*/  ETS_INTR_UNLOCK () ; 
 int RX_BUFF_SIZE ; 
 TYPE_2__ UartDev ; 

bool uart_getc(char *c){
    RcvMsgBuff *pRxBuff = &(UartDev.rcv_buff);
    if(pRxBuff->pWritePos == pRxBuff->pReadPos){   // empty
        return false;
    }
    // ETS_UART_INTR_DISABLE();
    ETS_INTR_LOCK();
    *c = (char)*(pRxBuff->pReadPos);
    if (pRxBuff->pReadPos == (pRxBuff->pRcvMsgBuff + RX_BUFF_SIZE)) {
        pRxBuff->pReadPos = pRxBuff->pRcvMsgBuff ;
    } else {
        pRxBuff->pReadPos++;
    }
    // ETS_UART_INTR_ENABLE();
    ETS_INTR_UNLOCK();
    return true;
}