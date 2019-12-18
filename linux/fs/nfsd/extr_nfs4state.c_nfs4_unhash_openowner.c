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
struct nfs4_stateowner {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  openowner (struct nfs4_stateowner*) ; 
 int /*<<< orphan*/  unhash_openowner_locked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_unhash_openowner(struct nfs4_stateowner *so)
{
	unhash_openowner_locked(openowner(so));
}