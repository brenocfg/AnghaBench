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
typedef  int umode_t ;
typedef  int u32 ;

/* Variables and functions */
 int FIBF_GRP_EXECUTE ; 
 int FIBF_GRP_READ ; 
 int FIBF_GRP_WRITE ; 
 int FIBF_NOEXECUTE ; 
 int FIBF_NOREAD ; 
 int FIBF_NOWRITE ; 
 int FIBF_OTR_EXECUTE ; 
 int FIBF_OTR_READ ; 
 int FIBF_OTR_WRITE ; 

umode_t
affs_prot_to_mode(u32 prot)
{
	umode_t mode = 0;

	if (!(prot & FIBF_NOWRITE))
		mode |= 0200;
	if (!(prot & FIBF_NOREAD))
		mode |= 0400;
	if (!(prot & FIBF_NOEXECUTE))
		mode |= 0100;
	if (prot & FIBF_GRP_WRITE)
		mode |= 0020;
	if (prot & FIBF_GRP_READ)
		mode |= 0040;
	if (prot & FIBF_GRP_EXECUTE)
		mode |= 0010;
	if (prot & FIBF_OTR_WRITE)
		mode |= 0002;
	if (prot & FIBF_OTR_READ)
		mode |= 0004;
	if (prot & FIBF_OTR_EXECUTE)
		mode |= 0001;

	return mode;
}