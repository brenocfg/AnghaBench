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
struct nfs_open_context {int dummy; } ;
struct nfs4_layoutget {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void pnfs_parse_lgopen(struct inode *ino,
		struct nfs4_layoutget *lgp,
		struct nfs_open_context *ctx)
{
}