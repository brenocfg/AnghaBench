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
struct nfs4_client {scalar_t__ cl_cb_state; scalar_t__ cl_minorversion; } ;

/* Variables and functions */
 scalar_t__ NFSD4_CB_UNKNOWN ; 
 scalar_t__ NFSD4_CB_UP ; 

__attribute__((used)) static bool nfsd4_cb_channel_good(struct nfs4_client *clp)
{
	if (clp->cl_cb_state == NFSD4_CB_UP)
		return true;
	/*
	 * In the sessions case, since we don't have to establish a
	 * separate connection for callbacks, we assume it's OK
	 * until we hear otherwise:
	 */
	return clp->cl_minorversion && clp->cl_cb_state == NFSD4_CB_UNKNOWN;
}