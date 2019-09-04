#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* conn; } ;
typedef  TYPE_1__ lwIP_sock ;
struct TYPE_10__ {scalar_t__ state; TYPE_2__* tcp; } ;
struct TYPE_9__ {scalar_t__ state; } ;

/* Variables and functions */
 int ERR_OK ; 
 scalar_t__ LISTEN ; 
 scalar_t__ NETCONN_STATE_ERROR ; 
 int /*<<< orphan*/  free_netconn (TYPE_4__*) ; 
 int /*<<< orphan*/  free_socket (TYPE_1__*) ; 
 TYPE_1__* get_socket (int) ; 
 int /*<<< orphan*/ * recv_tcp ; 
 int /*<<< orphan*/  remove_tcp (TYPE_4__*) ; 
 int tcp_close (TYPE_2__*) ; 
 int /*<<< orphan*/  tcp_recv (TYPE_2__*,int /*<<< orphan*/ *) ; 

int lwip_close(int s)
{
    lwIP_sock *sock = NULL;
    int err = 0;

    sock = get_socket(s);
    if (!sock)
    {
        return -1;
    }

    /*Do not set callback function when tcp->state is LISTEN.
    Avoid memory overlap when conn->tcp changes from
    struct tcp_bcb to struct tcp_pcb_listen after lwip_listen.*/
    if (sock->conn->tcp->state != LISTEN)
    {
        if (sock->conn->state != NETCONN_STATE_ERROR){
            tcp_recv(sock->conn->tcp, NULL);
            err = tcp_close(sock->conn->tcp);

            if (err != ERR_OK)
            {
                /* closing failed, try again later */
                tcp_recv(sock->conn->tcp, recv_tcp);
                return -1;
            }
        }
        /* closing succeeded */
        remove_tcp(sock->conn);
    } else {
        tcp_close(sock->conn->tcp);
    }
    free_netconn(sock->conn);
    free_socket(sock);
    return ERR_OK;
}