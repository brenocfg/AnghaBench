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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ ipc_base; } ;

/* Variables and functions */
 scalar_t__ IPC_STATUS ; 
 TYPE_1__ ipcdev ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline u32 ipc_read_status(void)
{
	return readl(ipcdev.ipc_base + IPC_STATUS);
}