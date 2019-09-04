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
struct super_block {int dummy; } ;
struct nfs_parsed_mount_data {int dummy; } ;
struct nfs_clone_mount {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void nfs_get_cache_cookie(struct super_block *sb,
				 struct nfs_parsed_mount_data *parsed,
				 struct nfs_clone_mount *cloned)
{
}