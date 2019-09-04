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
struct ft_sess {int /*<<< orphan*/  se_sess; } ;
struct ft_cmd {int /*<<< orphan*/  se_cmd; struct fc_frame* req_frame; struct ft_sess* sess; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_seq_release (scalar_t__) ; 
 scalar_t__ fr_seq (struct fc_frame*) ; 
 int /*<<< orphan*/  ft_sess_put (struct ft_sess*) ; 
 int /*<<< orphan*/  target_free_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ft_free_cmd(struct ft_cmd *cmd)
{
	struct fc_frame *fp;
	struct ft_sess *sess;

	if (!cmd)
		return;
	sess = cmd->sess;
	fp = cmd->req_frame;
	if (fr_seq(fp))
		fc_seq_release(fr_seq(fp));
	fc_frame_free(fp);
	target_free_tag(sess->se_sess, &cmd->se_cmd);
	ft_sess_put(sess);	/* undo get from lookup at recv */
}