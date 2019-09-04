#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int bigger_ack_num; } ;

/* Variables and functions */
 int MAX_TCP_SESSION ; 
 TYPE_1__* ack_session_info ; 

__attribute__((used)) static inline int update_tcp_session(u32 index, u32 ack)
{
	if (index < 2 * MAX_TCP_SESSION &&
	    ack > ack_session_info[index].bigger_ack_num)
		ack_session_info[index].bigger_ack_num = ack;
	return 0;
}