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
typedef  int u16 ;

/* Variables and functions */
 int IPC_HEADER_DATA_MASK ; 
 int IPC_HEADER_DATA_SHIFT ; 

__attribute__((used)) static inline u16 sst_byt_header_data(u64 header)
{
	return (header >> IPC_HEADER_DATA_SHIFT) & IPC_HEADER_DATA_MASK;
}