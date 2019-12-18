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
typedef  int u32 ;

/* Variables and functions */
 int IPC_STR_TYPE_MASK ; 
 int IPC_STR_TYPE_SHIFT ; 

__attribute__((used)) static inline u32 msg_get_stream_type(u32 msg)
{
	return (msg & IPC_STR_TYPE_MASK) >>  IPC_STR_TYPE_SHIFT;
}