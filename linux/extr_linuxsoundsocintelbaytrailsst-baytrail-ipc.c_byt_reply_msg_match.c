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
typedef  int u64 ;

/* Variables and functions */
 int IPC_HEADER_MSG_ID_MASK ; 
 int IPC_HEADER_STR_ID_MASK ; 
 int IPC_HEADER_STR_ID_SHIFT ; 

__attribute__((used)) static u64 byt_reply_msg_match(u64 header, u64 *mask)
{
	/* match reply to message sent based on msg and stream IDs */
	*mask = IPC_HEADER_MSG_ID_MASK |
	       IPC_HEADER_STR_ID_MASK << IPC_HEADER_STR_ID_SHIFT;
	header &= *mask;

	return header;
}