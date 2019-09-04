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
typedef  int /*<<< orphan*/  u8 ;
struct ath6kl {TYPE_1__* hif_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pipe_get_default ) (struct ath6kl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HIF ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct ath6kl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ath6kl_hif_pipe_get_default(struct ath6kl *ar,
					       u8 *ul_pipe, u8 *dl_pipe)
{
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif pipe get default\n");

	ar->hif_ops->pipe_get_default(ar, ul_pipe, dl_pipe);
}