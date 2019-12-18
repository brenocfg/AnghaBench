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
struct splice_desc {int num_spliced; } ;
struct pipe_inode_info {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  splice_actor ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  splice_from_pipe_begin (struct splice_desc*) ; 
 int /*<<< orphan*/  splice_from_pipe_end (struct pipe_inode_info*,struct splice_desc*) ; 
 int splice_from_pipe_feed (struct pipe_inode_info*,struct splice_desc*,int /*<<< orphan*/ *) ; 
 int splice_from_pipe_next (struct pipe_inode_info*,struct splice_desc*) ; 

ssize_t __splice_from_pipe(struct pipe_inode_info *pipe, struct splice_desc *sd,
			   splice_actor *actor)
{
	int ret;

	splice_from_pipe_begin(sd);
	do {
		cond_resched();
		ret = splice_from_pipe_next(pipe, sd);
		if (ret > 0)
			ret = splice_from_pipe_feed(pipe, sd, actor);
	} while (ret > 0);
	splice_from_pipe_end(pipe, sd);

	return sd->num_spliced ? sd->num_spliced : ret;
}