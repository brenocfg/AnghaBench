#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kernel_param {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_nmi ) (int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__ arch_kgdb_ops ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdb_nmi_disabled ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static int kdb_param_enable_nmi(const char *val, const struct kernel_param *kp)
{
	if (!atomic_add_unless(&kdb_nmi_disabled, -1, 0))
		return -EINVAL;
	arch_kgdb_ops.enable_nmi(1);
	return 0;
}