#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  gid; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {TYPE_1__ hdr; } ;
union ism_read_gid {TYPE_4__ response; TYPE_2__ request; } ;
struct ism_dev {TYPE_3__* smcd; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_7__ {int /*<<< orphan*/  local_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISM_READ_GID ; 
 int ism_cmd (struct ism_dev*,union ism_read_gid*) ; 
 int /*<<< orphan*/  memset (union ism_read_gid*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ism_read_local_gid(struct ism_dev *ism)
{
	union ism_read_gid cmd;
	int ret;

	memset(&cmd, 0, sizeof(cmd));
	cmd.request.hdr.cmd = ISM_READ_GID;
	cmd.request.hdr.len = sizeof(cmd.request);

	ret = ism_cmd(ism, &cmd);
	if (ret)
		goto out;

	ism->smcd->local_gid = cmd.response.gid;
out:
	return ret;
}