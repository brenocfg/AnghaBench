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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_desc_link ) (void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* ath9k_hw_ops (struct ath_hw*) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ath9k_hw_set_desc_link(struct ath_hw *ah, void *ds,
					  u32 link)
{
	ath9k_hw_ops(ah)->set_desc_link(ds, link);
}