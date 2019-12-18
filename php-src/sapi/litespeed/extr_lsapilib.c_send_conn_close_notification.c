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

/* Variables and functions */
 int /*<<< orphan*/  s_conn_close_pkt ; 
 int send_notification_pkt (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int send_conn_close_notification( int fd )
{
    return send_notification_pkt(fd, &s_conn_close_pkt);
}