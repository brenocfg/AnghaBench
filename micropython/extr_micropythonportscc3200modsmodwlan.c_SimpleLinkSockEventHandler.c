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
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_8__ {TYPE_2__ SockAsyncData; TYPE_1__ SockTxFailData; } ;
struct TYPE_9__ {int Event; TYPE_3__ socketAsyncEvent; } ;
typedef  TYPE_4__ SlSockEvent_t ;

/* Variables and functions */
#define  OTHER_SIDE_CLOSE_SSL_DATA_NOT_ENCRYPTED 133 
#define  RX_FRAGMENTATION_TOO_BIG 132 
#define  SL_ECLOSE 131 
#define  SL_SOCKET_ASYNC_EVENT 130 
#define  SL_SOCKET_TX_FAILED_EVENT 129 
#define  SSL_ACCEPT 128 

void SimpleLinkSockEventHandler(SlSockEvent_t *pSock) {
    if (!pSock) {
        return;
    }

    switch( pSock->Event ) {
    case SL_SOCKET_TX_FAILED_EVENT:
        switch( pSock->socketAsyncEvent.SockTxFailData.status) {
        case SL_ECLOSE:
            break;
        default:
          break;
        }
        break;
    case SL_SOCKET_ASYNC_EVENT:
         switch(pSock->socketAsyncEvent.SockAsyncData.type) {
         case SSL_ACCEPT:
             break;
         case RX_FRAGMENTATION_TOO_BIG:
             break;
         case OTHER_SIDE_CLOSE_SSL_DATA_NOT_ENCRYPTED:
             break;
         default:
             break;
         }
        break;
    default:
      break;
    }
}