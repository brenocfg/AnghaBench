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
struct nfsd4_compound_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_STATE_ID (struct nfsd4_compound_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURRENT_STATE_ID_FLAG ; 

void
clear_current_stateid(struct nfsd4_compound_state *cstate)
{
	CLEAR_STATE_ID(cstate, CURRENT_STATE_ID_FLAG);
}