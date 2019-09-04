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
struct cifsInodeInfo {int dummy; } ;
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPLOCK_READ ; 
 int /*<<< orphan*/  cifs_set_oplock_level (struct cifsInodeInfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cifs_downgrade_oplock(struct TCP_Server_Info *server,
			struct cifsInodeInfo *cinode, bool set_level2)
{
	if (set_level2)
		cifs_set_oplock_level(cinode, OPLOCK_READ);
	else
		cifs_set_oplock_level(cinode, 0);
}