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
struct rpc_cred {int dummy; } ;
struct auth_cred {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
nul_match(struct auth_cred *acred, struct rpc_cred *cred, int taskflags)
{
	return 1;
}