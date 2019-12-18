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
struct dlm_query_region {int dummy; } ;
struct dlm_query_nodeinfo {int dummy; } ;
struct dlm_query_join_request {int dummy; } ;
struct dlm_cancel_join {int dummy; } ;
struct dlm_assert_joined {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_ASSERT_JOINED_MSG ; 
 int /*<<< orphan*/  DLM_CANCEL_JOIN_MSG ; 
 int /*<<< orphan*/  DLM_MOD_KEY ; 
 int /*<<< orphan*/  DLM_QUERY_JOIN_MSG ; 
 int /*<<< orphan*/  DLM_QUERY_NODEINFO ; 
 int /*<<< orphan*/  DLM_QUERY_REGION ; 
 int /*<<< orphan*/  dlm_assert_joined_handler ; 
 int /*<<< orphan*/  dlm_cancel_join_handler ; 
 int /*<<< orphan*/  dlm_join_handlers ; 
 int /*<<< orphan*/  dlm_query_join_handler ; 
 int /*<<< orphan*/  dlm_query_nodeinfo_handler ; 
 int /*<<< orphan*/  dlm_query_region_handler ; 
 int /*<<< orphan*/  dlm_unregister_net_handlers () ; 
 int o2net_register_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_register_net_handlers(void)
{
	int status = 0;

	status = o2net_register_handler(DLM_QUERY_JOIN_MSG, DLM_MOD_KEY,
					sizeof(struct dlm_query_join_request),
					dlm_query_join_handler,
					NULL, NULL, &dlm_join_handlers);
	if (status)
		goto bail;

	status = o2net_register_handler(DLM_ASSERT_JOINED_MSG, DLM_MOD_KEY,
					sizeof(struct dlm_assert_joined),
					dlm_assert_joined_handler,
					NULL, NULL, &dlm_join_handlers);
	if (status)
		goto bail;

	status = o2net_register_handler(DLM_CANCEL_JOIN_MSG, DLM_MOD_KEY,
					sizeof(struct dlm_cancel_join),
					dlm_cancel_join_handler,
					NULL, NULL, &dlm_join_handlers);
	if (status)
		goto bail;

	status = o2net_register_handler(DLM_QUERY_REGION, DLM_MOD_KEY,
					sizeof(struct dlm_query_region),
					dlm_query_region_handler,
					NULL, NULL, &dlm_join_handlers);

	if (status)
		goto bail;

	status = o2net_register_handler(DLM_QUERY_NODEINFO, DLM_MOD_KEY,
					sizeof(struct dlm_query_nodeinfo),
					dlm_query_nodeinfo_handler,
					NULL, NULL, &dlm_join_handlers);
bail:
	if (status < 0)
		dlm_unregister_net_handlers();

	return status;
}