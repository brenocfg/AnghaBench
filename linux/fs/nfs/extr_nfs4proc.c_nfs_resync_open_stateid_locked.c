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
struct nfs4_state {int /*<<< orphan*/  flags; scalar_t__ n_rdwr; scalar_t__ n_rdonly; scalar_t__ n_wronly; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_OPEN_STATE ; 
 int /*<<< orphan*/  NFS_O_RDONLY_STATE ; 
 int /*<<< orphan*/  NFS_O_RDWR_STATE ; 
 int /*<<< orphan*/  NFS_O_WRONLY_STATE ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_resync_open_stateid_locked(struct nfs4_state *state)
{
	if (!(state->n_wronly || state->n_rdonly || state->n_rdwr))
		return;
	if (state->n_wronly)
		set_bit(NFS_O_WRONLY_STATE, &state->flags);
	if (state->n_rdonly)
		set_bit(NFS_O_RDONLY_STATE, &state->flags);
	if (state->n_rdwr)
		set_bit(NFS_O_RDWR_STATE, &state->flags);
	set_bit(NFS_OPEN_STATE, &state->flags);
}