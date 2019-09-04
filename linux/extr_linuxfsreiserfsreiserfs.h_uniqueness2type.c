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
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int TYPE_ANY ; 
 int TYPE_DIRECT ; 
 int TYPE_DIRENTRY ; 
 int TYPE_INDIRECT ; 
 int TYPE_STAT_DATA ; 
#define  V1_ANY_UNIQUENESS 132 
#define  V1_DIRECT_UNIQUENESS 131 
#define  V1_DIRENTRY_UNIQUENESS 130 
#define  V1_INDIRECT_UNIQUENESS 129 
#define  V1_SD_UNIQUENESS 128 

__attribute__((used)) static inline int uniqueness2type(__u32 uniqueness)
{
	switch ((int)uniqueness) {
	case V1_SD_UNIQUENESS:
		return TYPE_STAT_DATA;
	case V1_INDIRECT_UNIQUENESS:
		return TYPE_INDIRECT;
	case V1_DIRECT_UNIQUENESS:
		return TYPE_DIRECT;
	case V1_DIRENTRY_UNIQUENESS:
		return TYPE_DIRENTRY;
	case V1_ANY_UNIQUENESS:
	default:
		return TYPE_ANY;
	}
}