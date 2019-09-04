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
struct xdp_umem_reg {int dummy; } ;
struct xdp_umem {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct xdp_umem* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct xdp_umem*) ; 
 struct xdp_umem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int xdp_umem_reg (struct xdp_umem*,struct xdp_umem_reg*) ; 

struct xdp_umem *xdp_umem_create(struct xdp_umem_reg *mr)
{
	struct xdp_umem *umem;
	int err;

	umem = kzalloc(sizeof(*umem), GFP_KERNEL);
	if (!umem)
		return ERR_PTR(-ENOMEM);

	err = xdp_umem_reg(umem, mr);
	if (err) {
		kfree(umem);
		return ERR_PTR(err);
	}

	return umem;
}