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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */

__attribute__((used)) static ut64 get_vaddr(RBinFile *bf, ut64 baddr, ut64 paddr, ut64 vaddr) {
	return vaddr;
}