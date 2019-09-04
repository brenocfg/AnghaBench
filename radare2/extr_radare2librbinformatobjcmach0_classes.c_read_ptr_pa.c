#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  mach0_ut ;
struct TYPE_7__ {TYPE_2__* o; int /*<<< orphan*/  buf; } ;
struct TYPE_6__ {TYPE_1__* info; } ;
struct TYPE_5__ {int /*<<< orphan*/  big_endian; } ;
typedef  TYPE_3__ RBinFile ;

/* Variables and functions */
 int r_buf_read_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  r_read_ble (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool read_ptr_pa(RBinFile *bf, ut64 paddr, mach0_ut *out) {
	r_return_val_if_fail (out, false);
	r_return_val_if_fail (bf && bf->o && bf->o->info, false);

	size_t ptr_size = sizeof (mach0_ut);
	ut8 pp[sizeof (mach0_ut)] = {0};

	int len = r_buf_read_at (bf->buf, paddr, pp, ptr_size);
	if (len != ptr_size) {
		return false;
	}

	mach0_ut p = r_read_ble (&pp[0], bf->o->info->big_endian, 8 * ptr_size);
	*out = p;

	return true;
}