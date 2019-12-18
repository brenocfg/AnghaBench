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
struct egg_patch_t {int /*<<< orphan*/  b; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct egg_patch_t*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ ) ; 

void egg_patch_free (void *p) {
	struct egg_patch_t *ep = (struct egg_patch_t *)p;
	r_buf_free (ep->b);
	free (ep);
}