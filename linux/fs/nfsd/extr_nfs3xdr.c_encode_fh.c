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
struct TYPE_2__ {unsigned int fh_size; int /*<<< orphan*/  fh_base; } ;
struct svc_fh {TYPE_1__ fh_handle; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int XDR_QUADLEN (unsigned int) ; 
 int /*<<< orphan*/  htonl (unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static __be32 *
encode_fh(__be32 *p, struct svc_fh *fhp)
{
	unsigned int size = fhp->fh_handle.fh_size;
	*p++ = htonl(size);
	if (size) p[XDR_QUADLEN(size)-1]=0;
	memcpy(p, &fhp->fh_handle.fh_base, size);
	return p + XDR_QUADLEN(size);
}