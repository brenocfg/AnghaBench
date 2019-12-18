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
struct cifs_tcon {int dummy; } ;
struct cifs_fid {int /*<<< orphan*/  netfid; } ;
struct cifsInodeInfo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int CIFSSMBLock (int /*<<< orphan*/ ,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ CIFS_CACHE_READ (struct cifsInodeInfo*) ; 
 int /*<<< orphan*/  LOCKING_ANDX_OPLOCK_RELEASE ; 
 TYPE_1__* current ; 

__attribute__((used)) static int
cifs_oplock_response(struct cifs_tcon *tcon, struct cifs_fid *fid,
		     struct cifsInodeInfo *cinode)
{
	return CIFSSMBLock(0, tcon, fid->netfid, current->tgid, 0, 0, 0, 0,
			   LOCKING_ANDX_OPLOCK_RELEASE, false,
			   CIFS_CACHE_READ(cinode) ? 1 : 0);
}