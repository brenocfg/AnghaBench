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
struct kvec {int dummy; } ;
struct cifs_io_parms {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
struct cifs_fid {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;

/* Variables and functions */
 int SMB2_write (unsigned int const,struct cifs_io_parms*,unsigned int*,struct kvec*,unsigned long) ; 

__attribute__((used)) static int
smb2_sync_write(const unsigned int xid, struct cifs_fid *pfid,
		struct cifs_io_parms *parms, unsigned int *written,
		struct kvec *iov, unsigned long nr_segs)
{

	parms->persistent_fid = pfid->persistent_fid;
	parms->volatile_fid = pfid->volatile_fid;
	return SMB2_write(xid, parms, written, iov, nr_segs);
}