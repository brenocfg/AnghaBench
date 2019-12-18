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
struct btrfs_feature_attr {int dummy; } ;
struct attribute {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_to_btrfs_attr (struct attribute*) ; 
 struct btrfs_feature_attr* to_btrfs_feature_attr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct btrfs_feature_attr *attr_to_btrfs_feature_attr(
		struct attribute *attr)
{
	return to_btrfs_feature_attr(attr_to_btrfs_attr(attr));
}