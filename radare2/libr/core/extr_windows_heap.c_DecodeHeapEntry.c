#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
typedef  int UINT32 ;
struct TYPE_9__ {int EncodeFlagMask; int /*<<< orphan*/  Encoding; } ;
struct TYPE_8__ {TYPE_2__* bits; } ;
typedef  TYPE_1__ RDebug ;
typedef  TYPE_2__* PHEAP_ENTRY ;
typedef  TYPE_2__* PHEAP ;
typedef  int BYTE ;

/* Variables and functions */
 TYPE_2__* R_SYS_BITS_64 ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int) ; 

__attribute__((used)) static bool DecodeHeapEntry(RDebug *dbg, PHEAP heap, PHEAP_ENTRY entry) {
	r_return_val_if_fail (heap && entry, false);
	if (dbg->bits == R_SYS_BITS_64) {
		entry = (WPARAM)entry + dbg->bits;
	}
	if (heap->EncodeFlagMask && (*(UINT32 *)entry & heap->EncodeFlagMask)) {
		if (dbg->bits == R_SYS_BITS_64) {
			heap = (WPARAM)heap + dbg->bits;
		}
		*(WPARAM *)entry ^= *(WPARAM *)&heap->Encoding;
	}
	return !(((BYTE *)entry)[0] ^ ((BYTE *)entry)[1] ^ ((BYTE *)entry)[2] ^ ((BYTE *)entry)[3]);
}