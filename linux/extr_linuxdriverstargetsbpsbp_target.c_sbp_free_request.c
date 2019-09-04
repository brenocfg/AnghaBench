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
struct se_session {int dummy; } ;
struct se_cmd {struct se_session* se_sess; } ;
struct sbp_target_request {int /*<<< orphan*/  cmd_buf; int /*<<< orphan*/  pg_tbl; struct se_cmd se_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_free_tag (struct se_session*,struct se_cmd*) ; 

__attribute__((used)) static void sbp_free_request(struct sbp_target_request *req)
{
	struct se_cmd *se_cmd = &req->se_cmd;
	struct se_session *se_sess = se_cmd->se_sess;

	kfree(req->pg_tbl);
	kfree(req->cmd_buf);

	target_free_tag(se_sess, se_cmd);
}