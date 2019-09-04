#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_1__ RBinFile ;

/* Variables and functions */
 int check_buffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool load_bytes(RBinFile *bf, void **bin_obj, const ut8 *buf, ut64 sz, ut64 loadaddr, Sdb *sdb) {
	return check_buffer (bf->buf);
}