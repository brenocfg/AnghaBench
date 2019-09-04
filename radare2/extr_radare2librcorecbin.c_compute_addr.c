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
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  RBin ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 scalar_t__ rva (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static ut64 compute_addr(RBin *bin, ut64 paddr, ut64 vaddr, int va) {
	return paddr == UT64_MAX? vaddr: rva (bin, paddr, vaddr, va);
}