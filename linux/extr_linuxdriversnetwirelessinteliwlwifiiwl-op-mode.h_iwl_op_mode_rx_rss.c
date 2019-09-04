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
struct napi_struct {int dummy; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_op_mode {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rx_rss ) (struct iwl_op_mode*,struct napi_struct*,struct iwl_rx_cmd_buffer*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct iwl_op_mode*,struct napi_struct*,struct iwl_rx_cmd_buffer*,unsigned int) ; 

__attribute__((used)) static inline void iwl_op_mode_rx_rss(struct iwl_op_mode *op_mode,
				      struct napi_struct *napi,
				      struct iwl_rx_cmd_buffer *rxb,
				      unsigned int queue)
{
	op_mode->ops->rx_rss(op_mode, napi, rxb, queue);
}