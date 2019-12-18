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
struct sta_info {int /*<<< orphan*/  sta; int /*<<< orphan*/  rate_ctrl_lock; } ;
struct rate_control_ref {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {void* (* alloc_sta ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *rate_control_alloc_sta(struct rate_control_ref *ref,
					   struct sta_info *sta, gfp_t gfp)
{
	spin_lock_init(&sta->rate_ctrl_lock);
	return ref->ops->alloc_sta(ref->priv, &sta->sta, gfp);
}