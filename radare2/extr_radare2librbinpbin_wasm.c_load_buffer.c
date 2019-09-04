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
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 int /*<<< orphan*/  check_bytes_buf (int /*<<< orphan*/ *) ; 
 void* r_bin_wasm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *load_buffer(RBinFile *bf, RBuffer *buf, ut64 loadaddr, Sdb *sdb) {
	r_return_val_if_fail (bf && buf && r_buf_size (buf) != UT64_MAX, NULL);

	if (!check_bytes_buf (buf)) {
		return NULL;
	}
	return r_bin_wasm_init (bf, buf);
}