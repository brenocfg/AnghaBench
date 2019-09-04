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
struct r_bin_bflt_obj {int /*<<< orphan*/  b; struct r_bin_bflt_obj* hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (struct r_bin_bflt_obj*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ ) ; 

void r_bin_bflt_free(struct r_bin_bflt_obj *obj) {
	if (obj) {
		R_FREE (obj->hdr);
		r_buf_free (obj->b);
		R_FREE (obj);
	}
}