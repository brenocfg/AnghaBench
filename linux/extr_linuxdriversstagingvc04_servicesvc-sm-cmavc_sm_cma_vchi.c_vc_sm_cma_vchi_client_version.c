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
struct vc_sm_version {int dummy; } ;
struct vc_sm_result_t {int dummy; } ;
struct sm_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_SM_MSG_TYPE_CLIENT_VERSION ; 
 int vc_sm_cma_vchi_send_msg (struct sm_instance*,int /*<<< orphan*/ ,struct vc_sm_version*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int vc_sm_cma_vchi_client_version(struct sm_instance *handle,
				  struct vc_sm_version *msg,
				  struct vc_sm_result_t *result,
				  u32 *cur_trans_id)
{
	return vc_sm_cma_vchi_send_msg(handle, VC_SM_MSG_TYPE_CLIENT_VERSION,
				   //msg, sizeof(*msg), result, sizeof(*result),
				   //cur_trans_id, 1);
				   msg, sizeof(*msg), NULL, 0,
				   cur_trans_id, 0);
}