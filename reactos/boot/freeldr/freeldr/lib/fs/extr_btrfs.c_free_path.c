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
struct btrfs_path {scalar_t__ tree_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FrLdrTempFree (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_BTRFS_NODE ; 

__attribute__((used)) static inline void free_path(struct btrfs_path *path)
{
    if (path->tree_buf) FrLdrTempFree(path->tree_buf, TAG_BTRFS_NODE);
}