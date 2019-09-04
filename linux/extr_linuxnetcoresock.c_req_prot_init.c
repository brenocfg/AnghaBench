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
struct request_sock_ops {int /*<<< orphan*/  slab; int /*<<< orphan*/  obj_size; int /*<<< orphan*/  slab_name; } ;
struct proto {int slab_flags; int /*<<< orphan*/  name; struct request_sock_ops* rsk_prot; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SLAB_ACCOUNT ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int req_prot_init(const struct proto *prot)
{
	struct request_sock_ops *rsk_prot = prot->rsk_prot;

	if (!rsk_prot)
		return 0;

	rsk_prot->slab_name = kasprintf(GFP_KERNEL, "request_sock_%s",
					prot->name);
	if (!rsk_prot->slab_name)
		return -ENOMEM;

	rsk_prot->slab = kmem_cache_create(rsk_prot->slab_name,
					   rsk_prot->obj_size, 0,
					   SLAB_ACCOUNT | prot->slab_flags,
					   NULL);

	if (!rsk_prot->slab) {
		pr_crit("%s: Can't create request sock SLAB cache!\n",
			prot->name);
		return -ENOMEM;
	}
	return 0;
}