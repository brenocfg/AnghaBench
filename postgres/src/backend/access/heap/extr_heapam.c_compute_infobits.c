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
typedef  int uint8 ;
typedef  int uint16 ;

/* Variables and functions */
 int HEAP_KEYS_UPDATED ; 
 int HEAP_XMAX_EXCL_LOCK ; 
 int HEAP_XMAX_IS_MULTI ; 
 int HEAP_XMAX_KEYSHR_LOCK ; 
 int HEAP_XMAX_LOCK_ONLY ; 
 int XLHL_KEYS_UPDATED ; 
 int XLHL_XMAX_EXCL_LOCK ; 
 int XLHL_XMAX_IS_MULTI ; 
 int XLHL_XMAX_KEYSHR_LOCK ; 
 int XLHL_XMAX_LOCK_ONLY ; 

__attribute__((used)) static uint8
compute_infobits(uint16 infomask, uint16 infomask2)
{
	return
		((infomask & HEAP_XMAX_IS_MULTI) != 0 ? XLHL_XMAX_IS_MULTI : 0) |
		((infomask & HEAP_XMAX_LOCK_ONLY) != 0 ? XLHL_XMAX_LOCK_ONLY : 0) |
		((infomask & HEAP_XMAX_EXCL_LOCK) != 0 ? XLHL_XMAX_EXCL_LOCK : 0) |
	/* note we ignore HEAP_XMAX_SHR_LOCK here */
		((infomask & HEAP_XMAX_KEYSHR_LOCK) != 0 ? XLHL_XMAX_KEYSHR_LOCK : 0) |
		((infomask2 & HEAP_KEYS_UPDATED) != 0 ?
		 XLHL_KEYS_UPDATED : 0);
}