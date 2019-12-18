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
struct hidp_session {int /*<<< orphan*/  hid; } ;
struct hidp_connadd_req {scalar_t__ rd_size; } ;

/* Variables and functions */
 int ENODEV ; 
 int hidp_setup_hid (struct hidp_session*,struct hidp_connadd_req const*) ; 
 int hidp_setup_input (struct hidp_session*,struct hidp_connadd_req const*) ; 

__attribute__((used)) static int hidp_session_dev_init(struct hidp_session *session,
				 const struct hidp_connadd_req *req)
{
	int ret;

	if (req->rd_size > 0) {
		ret = hidp_setup_hid(session, req);
		if (ret && ret != -ENODEV)
			return ret;
	}

	if (!session->hid) {
		ret = hidp_setup_input(session, req);
		if (ret < 0)
			return ret;
	}

	return 0;
}