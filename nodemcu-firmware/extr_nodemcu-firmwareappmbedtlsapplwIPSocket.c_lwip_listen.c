#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ lwIP_sock ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  ESP_LOG (char*,int,...) ; 
 TYPE_1__* get_socket (int) ; 
 scalar_t__ netconn_listen (int /*<<< orphan*/ ) ; 

int lwip_listen(int s, int backlog)
{
    lwIP_sock *sock = NULL;
    err_t err = ERR_OK;
    sock = get_socket(s);
    if (!sock)
    {
        return -1;
    }
    err = netconn_listen(sock->conn);
    if (err != ERR_OK)
    {
        ESP_LOG("lwip_connect(%d) failed, err=%d\n", s, err);
        return -1;
    }

    ESP_LOG("lwip_connect(%d) succeeded\n", s);

    return ERR_OK;
}