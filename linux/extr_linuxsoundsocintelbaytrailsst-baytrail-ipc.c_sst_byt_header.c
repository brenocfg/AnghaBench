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
 int IPC_HEADER_DATA (int) ; 
 int IPC_HEADER_LARGE (int) ; 
 int IPC_HEADER_MSG_ID (int) ; 
 int IPC_HEADER_STR_ID (int) ; 
 int SST_BYT_IPCX_BUSY ; 

__attribute__((used)) static inline u64 sst_byt_header(int msg_id, int data, bool large, int str_id)
{
	return IPC_HEADER_MSG_ID(msg_id) | IPC_HEADER_STR_ID(str_id) |
	       IPC_HEADER_LARGE(large) | IPC_HEADER_DATA(data) |
	       SST_BYT_IPCX_BUSY;
}