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
struct iwl_trans {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_pmi ) (struct iwl_trans*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct iwl_trans*,int) ; 

__attribute__((used)) static inline void iwl_trans_set_pmi(struct iwl_trans *trans, bool state)
{
	if (trans->ops->set_pmi)
		trans->ops->set_pmi(trans, state);
}