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
typedef  int /*<<< orphan*/  u32 ;
struct vgic_its_abi {int (* commit ) (struct vgic_its*) ;} ;
struct vgic_its {int /*<<< orphan*/  abi_rev; } ;

/* Variables and functions */
 int stub1 (struct vgic_its*) ; 
 struct vgic_its_abi* vgic_its_get_abi (struct vgic_its*) ; 

__attribute__((used)) static int vgic_its_set_abi(struct vgic_its *its, u32 rev)
{
	const struct vgic_its_abi *abi;

	its->abi_rev = rev;
	abi = vgic_its_get_abi(its);
	return abi->commit(its);
}