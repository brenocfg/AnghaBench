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
struct nfsd4_secinfo {int si_namelen; int /*<<< orphan*/  si_name; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int /*<<< orphan*/  SAVEMEM (int /*<<< orphan*/ ,int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 scalar_t__ check_filename (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p ; 
 scalar_t__ status ; 

__attribute__((used)) static __be32
nfsd4_decode_secinfo(struct nfsd4_compoundargs *argp,
		     struct nfsd4_secinfo *secinfo)
{
	DECODE_HEAD;

	READ_BUF(4);
	secinfo->si_namelen = be32_to_cpup(p++);
	READ_BUF(secinfo->si_namelen);
	SAVEMEM(secinfo->si_name, secinfo->si_namelen);
	status = check_filename(secinfo->si_name, secinfo->si_namelen);
	if (status)
		return status;
	DECODE_TAIL;
}