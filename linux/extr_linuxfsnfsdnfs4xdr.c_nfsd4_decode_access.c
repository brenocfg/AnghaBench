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
struct nfsd4_compoundargs {int dummy; } ;
struct nfsd4_access {int /*<<< orphan*/  ac_req_access; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p ; 

__attribute__((used)) static __be32
nfsd4_decode_access(struct nfsd4_compoundargs *argp, struct nfsd4_access *access)
{
	DECODE_HEAD;

	READ_BUF(4);
	access->ac_req_access = be32_to_cpup(p++);

	DECODE_TAIL;
}