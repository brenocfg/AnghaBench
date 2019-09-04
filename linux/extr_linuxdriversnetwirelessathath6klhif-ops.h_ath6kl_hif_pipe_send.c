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
struct sk_buff {int dummy; } ;
struct ath6kl {TYPE_1__* hif_ops; } ;
struct TYPE_2__ {int (* pipe_send ) (struct ath6kl*,int /*<<< orphan*/ ,struct sk_buff*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HIF ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct ath6kl*,int /*<<< orphan*/ ,struct sk_buff*,struct sk_buff*) ; 

__attribute__((used)) static inline int ath6kl_hif_pipe_send(struct ath6kl *ar,
				       u8 pipe, struct sk_buff *hdr_buf,
				       struct sk_buff *buf)
{
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif pipe send\n");

	return ar->hif_ops->pipe_send(ar, pipe, hdr_buf, buf);
}