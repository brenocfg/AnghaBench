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
struct dlm_protocol_version {int /*<<< orphan*/  pv_minor; int /*<<< orphan*/  pv_major; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_NOTICE ; 
 int /*<<< orphan*/  dlm_protocol_compare (struct dlm_protocol_version*,struct dlm_protocol_version*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_query_join_proto_check(char *proto_type, int node,
				      struct dlm_protocol_version *ours,
				      struct dlm_protocol_version *request)
{
	int rc;
	struct dlm_protocol_version proto = *request;

	if (!dlm_protocol_compare(ours, &proto)) {
		mlog(0,
		     "node %u wanted to join with %s locking protocol "
		     "%u.%u, we respond with %u.%u\n",
		     node, proto_type,
		     request->pv_major,
		     request->pv_minor,
		     proto.pv_major, proto.pv_minor);
		request->pv_minor = proto.pv_minor;
		rc = 0;
	} else {
		mlog(ML_NOTICE,
		     "Node %u wanted to join with %s locking "
		     "protocol %u.%u, but we have %u.%u, disallowing\n",
		     node, proto_type,
		     request->pv_major,
		     request->pv_minor,
		     ours->pv_major,
		     ours->pv_minor);
		rc = 1;
	}

	return rc;
}