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
struct TYPE_2__ {int /*<<< orphan*/  si_opaque; int /*<<< orphan*/  si_generation; } ;
struct nfsd4_free_stateid {TYPE_1__ fr_stateid; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  int /*<<< orphan*/  stateid_opaque_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  COPYMEM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p ; 

__attribute__((used)) static __be32
nfsd4_decode_free_stateid(struct nfsd4_compoundargs *argp,
			  struct nfsd4_free_stateid *free_stateid)
{
	DECODE_HEAD;

	READ_BUF(sizeof(stateid_t));
	free_stateid->fr_stateid.si_generation = be32_to_cpup(p++);
	COPYMEM(&free_stateid->fr_stateid.si_opaque, sizeof(stateid_opaque_t));

	DECODE_TAIL;
}