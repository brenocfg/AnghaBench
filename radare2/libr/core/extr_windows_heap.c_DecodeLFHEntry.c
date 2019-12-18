#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
struct TYPE_6__ {int /*<<< orphan*/  BaseAddress; scalar_t__ EncodeFlagMask; } ;
struct TYPE_5__ {scalar_t__ bits; } ;
typedef  TYPE_1__ RDebug ;
typedef  int /*<<< orphan*/  PHEAP_USERDATA_HEADER ;
typedef  int PHEAP_ENTRY ;
typedef  TYPE_2__* PHEAP ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int PtrToInt (int /*<<< orphan*/ ) ; 
 scalar_t__ R_SYS_BITS_64 ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int) ; 

__attribute__((used)) static bool DecodeLFHEntry(RDebug *dbg, PHEAP heap, PHEAP_ENTRY entry, PHEAP_USERDATA_HEADER userBlocks, WPARAM key, WPARAM addr) {
	r_return_val_if_fail (heap && entry, false);
	if (dbg->bits == R_SYS_BITS_64) {
		entry = (WPARAM)entry + dbg->bits;
	}

	if (heap->EncodeFlagMask) {
		*(DWORD *)entry ^= PtrToInt (heap->BaseAddress) ^ (DWORD)(((DWORD)addr - PtrToInt (userBlocks)) << 0xC) ^ (DWORD)key ^ (addr >> 4);
	}
	return !(((BYTE *)entry)[0] ^ ((BYTE *)entry)[1] ^ ((BYTE *)entry)[2] ^ ((BYTE *)entry)[3]);
}