#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cifsInodeInfo {int dummy; } ;
struct TCP_Server_Info {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_oplock_level ) (struct cifsInodeInfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SMB2_OPLOCK_LEVEL_II ; 
 int /*<<< orphan*/  stub1 (struct cifsInodeInfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct cifsInodeInfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
smb2_downgrade_oplock(struct TCP_Server_Info *server,
			struct cifsInodeInfo *cinode, bool set_level2)
{
	if (set_level2)
		server->ops->set_oplock_level(cinode, SMB2_OPLOCK_LEVEL_II,
						0, NULL);
	else
		server->ops->set_oplock_level(cinode, 0, 0, NULL);
}