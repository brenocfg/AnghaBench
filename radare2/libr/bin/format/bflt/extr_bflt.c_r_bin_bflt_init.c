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
struct r_bin_bflt_obj {int endian; int /*<<< orphan*/ * hdr; scalar_t__ n_got; int /*<<< orphan*/ * got_table; int /*<<< orphan*/ * reloc_table; int /*<<< orphan*/  size; int /*<<< orphan*/  b; } ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  bflt_init_hdr (struct r_bin_bflt_obj*) ; 
 int /*<<< orphan*/  r_buf_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_buf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r_bin_bflt_init(struct r_bin_bflt_obj *obj, RBuffer *buf) {
	obj->b = r_buf_ref (buf);
	obj->size = r_buf_size (buf);
	obj->endian = false;
	obj->reloc_table = NULL;
	obj->got_table = NULL;
	obj->n_got = 0;
	obj->hdr = NULL;
	if (!bflt_init_hdr (obj)) {
		return false;
	}
	return true;
}