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
struct nfs4_client {scalar_t__ cl_time; } ;

/* Variables and functions */

__attribute__((used)) static bool is_client_expired(struct nfs4_client *clp)
{
	return clp->cl_time == 0;
}