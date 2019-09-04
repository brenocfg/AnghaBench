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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  check_bytes (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_buf_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* r_buf_new () ; 

__attribute__((used)) static void *load_buffer(RBinFile *bf, RBuffer *buf, ut64 loadaddr, Sdb *sdb) {
	ut64 tmpsz;
	const ut8 *tmp = r_buf_buffer (buf, &tmpsz);
	if (!check_bytes (tmp, tmpsz)) {
		return NULL;
	}
	return r_buf_new ();
}