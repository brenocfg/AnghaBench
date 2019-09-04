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
struct nfs_server {int dummy; } ;
struct nfs4_threshold {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
pnfs_use_threshold(struct nfs4_threshold **dst, struct nfs4_threshold *src,
		   struct nfs_server *nfss)
{
	return false;
}