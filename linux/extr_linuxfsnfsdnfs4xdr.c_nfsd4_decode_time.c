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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserr_inval ; 
 int /*<<< orphan*/  p ; 
 int /*<<< orphan*/  xdr_decode_hyper (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_decode_time(struct nfsd4_compoundargs *argp, struct timespec *tv)
{
	DECODE_HEAD;
	u64 sec;

	READ_BUF(12);
	p = xdr_decode_hyper(p, &sec);
	tv->tv_sec = sec;
	tv->tv_nsec = be32_to_cpup(p++);
	if (tv->tv_nsec >= (u32)1000000000)
		return nfserr_inval;

	DECODE_TAIL;
}