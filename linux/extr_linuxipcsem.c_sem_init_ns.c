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
struct ipc_namespace {int /*<<< orphan*/ * ids; scalar_t__ used_sems; int /*<<< orphan*/  sc_semmni; int /*<<< orphan*/  sc_semopm; int /*<<< orphan*/  sc_semmns; int /*<<< orphan*/  sc_semmsl; } ;

/* Variables and functions */
 size_t IPC_SEM_IDS ; 
 int /*<<< orphan*/  SEMMNI ; 
 int /*<<< orphan*/  SEMMNS ; 
 int /*<<< orphan*/  SEMMSL ; 
 int /*<<< orphan*/  SEMOPM ; 
 int /*<<< orphan*/  ipc_init_ids (int /*<<< orphan*/ *) ; 

void sem_init_ns(struct ipc_namespace *ns)
{
	ns->sc_semmsl = SEMMSL;
	ns->sc_semmns = SEMMNS;
	ns->sc_semopm = SEMOPM;
	ns->sc_semmni = SEMMNI;
	ns->used_sems = 0;
	ipc_init_ids(&ns->ids[IPC_SEM_IDS]);
}