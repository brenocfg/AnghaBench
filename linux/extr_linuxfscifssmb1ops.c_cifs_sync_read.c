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
struct cifs_io_parms {int /*<<< orphan*/  netfid; } ;
struct cifs_fid {int /*<<< orphan*/  netfid; } ;

/* Variables and functions */
 int CIFSSMBRead (unsigned int const,struct cifs_io_parms*,unsigned int*,char**,int*) ; 

__attribute__((used)) static int
cifs_sync_read(const unsigned int xid, struct cifs_fid *pfid,
	       struct cifs_io_parms *parms, unsigned int *bytes_read,
	       char **buf, int *buf_type)
{
	parms->netfid = pfid->netfid;
	return CIFSSMBRead(xid, parms, bytes_read, buf, buf_type);
}