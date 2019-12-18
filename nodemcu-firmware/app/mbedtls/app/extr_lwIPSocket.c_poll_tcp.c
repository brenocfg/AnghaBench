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
struct tcp_pcb {int dummy; } ;
typedef  int /*<<< orphan*/  lwIP_netconn ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  lwIP_ASSERT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static err_t poll_tcp(void *arg, struct tcp_pcb *pcb)
{
    lwIP_netconn *conn = arg;
    lwIP_ASSERT(conn);

    return ERR_OK;
}