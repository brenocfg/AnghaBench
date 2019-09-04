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
struct TYPE_2__ {int /*<<< orphan*/  fh_base; } ;
struct svc_fh {TYPE_1__ fh_handle; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS_FHSIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __be32 *
encode_fh(__be32 *p, struct svc_fh *fhp)
{
	memcpy(p, &fhp->fh_handle.fh_base, NFS_FHSIZE);
	return p + (NFS_FHSIZE>> 2);
}