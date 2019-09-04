#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int maxreqs; } ;
struct nfsd4_session {TYPE_2__** se_slots; TYPE_1__ se_fchannel; } ;
struct TYPE_4__ {int /*<<< orphan*/  sl_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_svc_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void
free_session_slots(struct nfsd4_session *ses)
{
	int i;

	for (i = 0; i < ses->se_fchannel.maxreqs; i++) {
		free_svc_cred(&ses->se_slots[i]->sl_cred);
		kfree(ses->se_slots[i]);
	}
}