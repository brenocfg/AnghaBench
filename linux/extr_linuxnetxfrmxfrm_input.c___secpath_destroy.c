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
struct sec_path {int len; int /*<<< orphan*/ * xvec; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sec_path*) ; 
 int /*<<< orphan*/  secpath_cachep ; 
 int /*<<< orphan*/  xfrm_state_put (int /*<<< orphan*/ ) ; 

void __secpath_destroy(struct sec_path *sp)
{
	int i;
	for (i = 0; i < sp->len; i++)
		xfrm_state_put(sp->xvec[i]);
	kmem_cache_free(secpath_cachep, sp);
}