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
struct request_sock_ops {int /*<<< orphan*/ * slab; int /*<<< orphan*/ * slab_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void req_prot_cleanup(struct request_sock_ops *rsk_prot)
{
	if (!rsk_prot)
		return;
	kfree(rsk_prot->slab_name);
	rsk_prot->slab_name = NULL;
	kmem_cache_destroy(rsk_prot->slab);
	rsk_prot->slab = NULL;
}