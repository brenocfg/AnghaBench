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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS2_SATTR_NOT_SET ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 *xdr_time_not_set(__be32 *p)
{
	*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);
	*p++ = cpu_to_be32(NFS2_SATTR_NOT_SET);
	return p;
}