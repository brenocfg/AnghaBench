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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPCAUTH_EOF ; 
 int /*<<< orphan*/  RPCAUTH_info ; 
 int /*<<< orphan*/  authfiles ; 
 int rpc_populate (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int rpc_clntdir_populate(struct dentry *dentry, void *private)
{
	return rpc_populate(dentry,
			    authfiles, RPCAUTH_info, RPCAUTH_EOF,
			    private);
}