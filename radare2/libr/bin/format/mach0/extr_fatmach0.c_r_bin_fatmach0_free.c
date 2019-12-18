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
struct r_bin_fatmach0_obj_t {int /*<<< orphan*/  b; int /*<<< orphan*/  archs; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (struct r_bin_fatmach0_obj_t*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ ) ; 

void* r_bin_fatmach0_free(struct r_bin_fatmach0_obj_t* bin) {
	if (!bin) {
		return NULL;
	}
	free (bin->archs);
	r_buf_free (bin->b);
	R_FREE (bin);
	return NULL;
}