#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_4__ {TYPE_1__* s_es; } ;
struct TYPE_3__ {scalar_t__ s_feature_compat; } ;

/* Variables and functions */
 TYPE_2__* EXT4_SB (struct super_block*) ; 

__attribute__((used)) static inline bool ext4_has_compat_features(struct super_block *sb)
{
	return (EXT4_SB(sb)->s_es->s_feature_compat != 0);
}