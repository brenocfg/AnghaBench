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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct nfsd4_sequence {void* cachethis; void* maxslots; void* slotid; void* seqid; TYPE_1__ sessionid; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  COPYMEM (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 scalar_t__ NFS4_MAX_SESSIONID_LEN ; 
 int /*<<< orphan*/  READ_BUF (scalar_t__) ; 
 void* be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p ; 

__attribute__((used)) static __be32
nfsd4_decode_sequence(struct nfsd4_compoundargs *argp,
		      struct nfsd4_sequence *seq)
{
	DECODE_HEAD;

	READ_BUF(NFS4_MAX_SESSIONID_LEN + 16);
	COPYMEM(seq->sessionid.data, NFS4_MAX_SESSIONID_LEN);
	seq->seqid = be32_to_cpup(p++);
	seq->slotid = be32_to_cpup(p++);
	seq->maxslots = be32_to_cpup(p++);
	seq->cachethis = be32_to_cpup(p++);

	DECODE_TAIL;
}