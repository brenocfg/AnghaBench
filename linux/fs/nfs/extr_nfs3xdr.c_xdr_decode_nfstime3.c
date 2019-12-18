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
struct timespec {void* tv_nsec; void* tv_sec; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* be32_to_cpup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 *xdr_decode_nfstime3(__be32 *p, struct timespec *timep)
{
	timep->tv_sec = be32_to_cpup(p++);
	timep->tv_nsec = be32_to_cpup(p++);
	return p;
}