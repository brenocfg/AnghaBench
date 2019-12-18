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
struct cifs_open_parms {TYPE_3__* cifs_sb; TYPE_1__* fid; int /*<<< orphan*/  create_options; int /*<<< orphan*/  desired_access; int /*<<< orphan*/  disposition; int /*<<< orphan*/  path; TYPE_4__* tcon; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_8__ {TYPE_2__* ses; } ;
struct TYPE_7__ {int /*<<< orphan*/  local_nls; } ;
struct TYPE_6__ {int capabilities; } ;
struct TYPE_5__ {int /*<<< orphan*/  netfid; } ;
typedef  int /*<<< orphan*/  FILE_ALL_INFO ;

/* Variables and functions */
 int CAP_NT_SMBS ; 
 int CIFS_open (unsigned int const,struct cifs_open_parms*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SMBLegacyOpen (unsigned int const,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_remap (TYPE_3__*) ; 

__attribute__((used)) static int
cifs_open_file(const unsigned int xid, struct cifs_open_parms *oparms,
	       __u32 *oplock, FILE_ALL_INFO *buf)
{
	if (!(oparms->tcon->ses->capabilities & CAP_NT_SMBS))
		return SMBLegacyOpen(xid, oparms->tcon, oparms->path,
				     oparms->disposition,
				     oparms->desired_access,
				     oparms->create_options,
				     &oparms->fid->netfid, oplock, buf,
				     oparms->cifs_sb->local_nls,
				     cifs_remap(oparms->cifs_sb));
	return CIFS_open(xid, oparms, oplock, buf);
}