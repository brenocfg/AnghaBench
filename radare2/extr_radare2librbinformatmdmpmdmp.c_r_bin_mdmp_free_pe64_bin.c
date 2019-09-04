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
struct Pe64_r_bin_mdmp_pe_bin {TYPE_1__* bin; } ;
struct TYPE_2__ {int /*<<< orphan*/  kv; } ;

/* Variables and functions */
 int /*<<< orphan*/  Pe64_r_bin_pe_free (TYPE_1__*) ; 
 int /*<<< orphan*/  R_FREE (struct Pe64_r_bin_mdmp_pe_bin*) ; 
 int /*<<< orphan*/  sdb_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_bin_mdmp_free_pe64_bin(void *pe_bin_) {
	struct Pe64_r_bin_mdmp_pe_bin *pe_bin = pe_bin_;
	if (pe_bin) {
		sdb_free (pe_bin->bin->kv);
		Pe64_r_bin_pe_free (pe_bin->bin);
		R_FREE (pe_bin);
	}
}