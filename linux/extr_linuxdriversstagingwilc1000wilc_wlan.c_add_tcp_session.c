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
typedef  void* u32 ;
struct TYPE_2__ {void* dst_port; void* src_port; scalar_t__ bigger_ack_num; void* seq_num; } ;

/* Variables and functions */
 int MAX_TCP_SESSION ; 
 TYPE_1__* ack_session_info ; 
 int tcp_session ; 

__attribute__((used)) static inline int add_tcp_session(u32 src_prt, u32 dst_prt, u32 seq)
{
	if (tcp_session < 2 * MAX_TCP_SESSION) {
		ack_session_info[tcp_session].seq_num = seq;
		ack_session_info[tcp_session].bigger_ack_num = 0;
		ack_session_info[tcp_session].src_port = src_prt;
		ack_session_info[tcp_session].dst_port = dst_prt;
		tcp_session++;
	}
	return 0;
}