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
struct vgic_its_abi {int dummy; } ;
struct vgic_its {size_t abi_rev; } ;

/* Variables and functions */
 struct vgic_its_abi const* its_table_abi_versions ; 

inline const struct vgic_its_abi *vgic_its_get_abi(struct vgic_its *its)
{
	return &its_table_abi_versions[its->abi_rev];
}