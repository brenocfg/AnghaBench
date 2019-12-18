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
struct stat_session {int dummy; } ;
struct inode {struct stat_session* i_private; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_stat_session (struct stat_session*) ; 
 int seq_release (struct inode*,struct file*) ; 

__attribute__((used)) static int tracing_stat_release(struct inode *i, struct file *f)
{
	struct stat_session *session = i->i_private;

	reset_stat_session(session);

	return seq_release(i, f);
}