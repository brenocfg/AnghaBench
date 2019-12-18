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
struct nfs4_acl {int dummy; } ;
struct nfs4_ace {int dummy; } ;

/* Variables and functions */

int nfs4_acl_bytes(int entries)
{
	return sizeof(struct nfs4_acl) + entries * sizeof(struct nfs4_ace);
}