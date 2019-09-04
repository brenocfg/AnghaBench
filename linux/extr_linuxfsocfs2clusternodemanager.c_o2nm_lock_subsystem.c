#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  su_mutex; } ;
struct TYPE_4__ {TYPE_1__ cs_subsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 TYPE_2__ o2nm_cluster_group ; 

__attribute__((used)) static inline void o2nm_lock_subsystem(void)
{
	mutex_lock(&o2nm_cluster_group.cs_subsys.su_mutex);
}