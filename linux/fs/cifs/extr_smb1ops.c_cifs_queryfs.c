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
struct kstatfs {int /*<<< orphan*/  f_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  Capability; } ;
struct cifs_tcon {TYPE_1__* ses; TYPE_2__ fsUnixInfo; } ;
struct TYPE_3__ {int capabilities; } ;

/* Variables and functions */
 int CAP_NT_SMBS ; 
 int CAP_UNIX ; 
 int CIFSSMBQFSInfo (unsigned int const,struct cifs_tcon*,struct kstatfs*) ; 
 int CIFSSMBQFSPosixInfo (unsigned int const,struct cifs_tcon*,struct kstatfs*) ; 
 int /*<<< orphan*/  CIFS_MAGIC_NUMBER ; 
 int CIFS_POSIX_EXTENSIONS ; 
 int EOPNOTSUPP ; 
 int SMBOldQFSInfo (unsigned int const,struct cifs_tcon*,struct kstatfs*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cifs_queryfs(const unsigned int xid, struct cifs_tcon *tcon,
	     struct kstatfs *buf)
{
	int rc = -EOPNOTSUPP;

	buf->f_type = CIFS_MAGIC_NUMBER;

	/*
	 * We could add a second check for a QFS Unix capability bit
	 */
	if ((tcon->ses->capabilities & CAP_UNIX) &&
	    (CIFS_POSIX_EXTENSIONS & le64_to_cpu(tcon->fsUnixInfo.Capability)))
		rc = CIFSSMBQFSPosixInfo(xid, tcon, buf);

	/*
	 * Only need to call the old QFSInfo if failed on newer one,
	 * e.g. by OS/2.
	 **/
	if (rc && (tcon->ses->capabilities & CAP_NT_SMBS))
		rc = CIFSSMBQFSInfo(xid, tcon, buf);

	/*
	 * Some old Windows servers also do not support level 103, retry with
	 * older level one if old server failed the previous call or we
	 * bypassed it because we detected that this was an older LANMAN sess
	 */
	if (rc)
		rc = SMBOldQFSInfo(xid, tcon, buf);
	return rc;
}