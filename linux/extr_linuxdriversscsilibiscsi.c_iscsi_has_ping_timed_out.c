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
struct iscsi_conn {int recv_timeout; int ping_timeout; scalar_t__ last_recv; scalar_t__ ping_task; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_before_eq (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_has_ping_timed_out(struct iscsi_conn *conn)
{
	if (conn->ping_task &&
	    time_before_eq(conn->last_recv + (conn->recv_timeout * HZ) +
			   (conn->ping_timeout * HZ), jiffies))
		return 1;
	else
		return 0;
}