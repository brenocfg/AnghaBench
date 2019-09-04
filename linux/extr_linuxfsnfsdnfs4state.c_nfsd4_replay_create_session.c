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
struct nfsd4_create_session {int dummy; } ;
struct nfsd4_clid_slot {int /*<<< orphan*/  sl_status; int /*<<< orphan*/  sl_cr_ses; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct nfsd4_create_session*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __be32
nfsd4_replay_create_session(struct nfsd4_create_session *cr_ses,
			    struct nfsd4_clid_slot *slot)
{
	memcpy(cr_ses, &slot->sl_cr_ses, sizeof(*cr_ses));
	return slot->sl_status;
}