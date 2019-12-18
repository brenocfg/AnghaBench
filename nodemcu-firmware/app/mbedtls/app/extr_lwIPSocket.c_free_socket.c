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
struct TYPE_3__ {scalar_t__ send_index; int /*<<< orphan*/ * send_buffer; scalar_t__ recv_index; scalar_t__ recv_data_len; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ lwIP_sock ;

/* Variables and functions */

__attribute__((used)) static void free_socket(lwIP_sock *sock)
{
    void *lastdata = NULL;
    sock->conn = NULL;
    sock->recv_data_len = 0;
    sock->recv_index = 0;
    sock->send_buffer = NULL;
    sock->send_index = 0;
}