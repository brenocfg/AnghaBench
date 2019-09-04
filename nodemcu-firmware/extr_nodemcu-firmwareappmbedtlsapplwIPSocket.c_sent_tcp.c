#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16_t ;
struct tcp_pcb {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ lwIP_netconn ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  NETCONN_EVENT_SEND ; 
 int /*<<< orphan*/  NETCONN_STATE_ESTABLISHED ; 
 int /*<<< orphan*/  find_socket (TYPE_1__*) ; 
 int /*<<< orphan*/  lwIP_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  lwIP_EVENT_THREAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t sent_tcp(void *arg, struct tcp_pcb *pcb, u16_t len)
{
    lwIP_netconn *conn = arg;
    lwIP_ASSERT(conn);
    conn->state = NETCONN_STATE_ESTABLISHED;
	lwIP_EVENT_THREAD(find_socket(conn), NETCONN_EVENT_SEND, len);
    return ERR_OK;
}