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
struct ocfs2_control_message_down {char space1; char space2; char newline; int /*<<< orphan*/  uuid; int /*<<< orphan*/  nodestr; int /*<<< orphan*/  tag; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 long INT_MAX ; 
 long LONG_MAX ; 
 long LONG_MIN ; 
 scalar_t__ OCFS2_CONTROL_HANDSHAKE_VALID ; 
 int /*<<< orphan*/  OCFS2_CONTROL_MESSAGE_DOWN_OP ; 
 int /*<<< orphan*/  OCFS2_CONTROL_MESSAGE_OP_LEN ; 
 scalar_t__ ocfs2_control_get_handshake_state (struct file*) ; 
 int /*<<< orphan*/  ocfs2_control_send_down (int /*<<< orphan*/ ,long) ; 
 long simple_strtol (int /*<<< orphan*/ ,char**,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_control_do_down_msg(struct file *file,
				     struct ocfs2_control_message_down *msg)
{
	long nodenum;
	char *p = NULL;

	if (ocfs2_control_get_handshake_state(file) !=
	    OCFS2_CONTROL_HANDSHAKE_VALID)
		return -EINVAL;

	if (strncmp(msg->tag, OCFS2_CONTROL_MESSAGE_DOWN_OP,
		    OCFS2_CONTROL_MESSAGE_OP_LEN))
		return -EINVAL;

	if ((msg->space1 != ' ') || (msg->space2 != ' ') ||
	    (msg->newline != '\n'))
		return -EINVAL;
	msg->space1 = msg->space2 = msg->newline = '\0';

	nodenum = simple_strtol(msg->nodestr, &p, 16);
	if (!p || *p)
		return -EINVAL;

	if ((nodenum == LONG_MIN) || (nodenum == LONG_MAX) ||
	    (nodenum > INT_MAX) || (nodenum < 0))
		return -ERANGE;

	ocfs2_control_send_down(msg->uuid, nodenum);

	return 0;
}