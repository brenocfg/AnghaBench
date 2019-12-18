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
 int PROCESS_MSG ; 

__attribute__((used)) static inline bool sst_is_process_reply(u32 msg_id)
{
	return ((msg_id & PROCESS_MSG) ? true : false);
}