#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {TYPE_1__ h; } ;
struct fuse_req {struct fuse_args* args; TYPE_2__ in; } ;
struct fuse_args {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */

__attribute__((used)) static void fuse_args_to_req(struct fuse_req *req, struct fuse_args *args)
{
	req->in.h.opcode = args->opcode;
	req->in.h.nodeid = args->nodeid;
	req->args = args;
}