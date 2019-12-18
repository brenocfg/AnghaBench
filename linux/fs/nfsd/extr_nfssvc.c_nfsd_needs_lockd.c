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
struct nfsd_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_TEST ; 
 scalar_t__ nfsd_vers (struct nfsd_net*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nfsd_needs_lockd(struct nfsd_net *nn)
{
	return nfsd_vers(nn, 2, NFSD_TEST) || nfsd_vers(nn, 3, NFSD_TEST);
}