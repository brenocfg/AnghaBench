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
struct cifs_tcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFSSMBQFSAttributeInfo (unsigned int const,struct cifs_tcon*) ; 
 int /*<<< orphan*/  CIFSSMBQFSDeviceInfo (unsigned int const,struct cifs_tcon*) ; 

__attribute__((used)) static void
cifs_qfs_tcon(const unsigned int xid, struct cifs_tcon *tcon)
{
	CIFSSMBQFSDeviceInfo(xid, tcon);
	CIFSSMBQFSAttributeInfo(xid, tcon);
}