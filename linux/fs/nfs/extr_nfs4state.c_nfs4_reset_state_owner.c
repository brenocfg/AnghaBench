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
struct TYPE_2__ {int /*<<< orphan*/  create_time; } ;
struct nfs4_state_owner {TYPE_1__ so_seqid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void
nfs4_reset_state_owner(struct nfs4_state_owner *sp)
{
	/* This state_owner is no longer usable, but must
	 * remain in place so that state recovery can find it
	 * and the opens associated with it.
	 * It may also be used for new 'open' request to
	 * return a delegation to the server.
	 * So update the 'create_time' so that it looks like
	 * a new state_owner.  This will cause the server to
	 * request an OPEN_CONFIRM to start a new sequence.
	 */
	sp->so_seqid.create_time = ktime_get();
}