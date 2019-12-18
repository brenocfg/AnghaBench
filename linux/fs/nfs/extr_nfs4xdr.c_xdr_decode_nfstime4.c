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
typedef  scalar_t__ time_t ;
struct timespec {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
typedef  scalar_t__ __u64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static __be32 *
xdr_decode_nfstime4(__be32 *p, struct timespec *t)
{
	__u64 sec;

	p = xdr_decode_hyper(p, &sec);
	t-> tv_sec = (time_t)sec;
	t->tv_nsec = be32_to_cpup(p++);
	return p;
}