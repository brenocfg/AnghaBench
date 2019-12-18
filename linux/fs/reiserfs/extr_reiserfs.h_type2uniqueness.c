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
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
#define  TYPE_ANY 132 
#define  TYPE_DIRECT 131 
#define  TYPE_DIRENTRY 130 
#define  TYPE_INDIRECT 129 
#define  TYPE_STAT_DATA 128 
 int /*<<< orphan*/  V1_ANY_UNIQUENESS ; 
 int /*<<< orphan*/  V1_DIRECT_UNIQUENESS ; 
 int /*<<< orphan*/  V1_DIRENTRY_UNIQUENESS ; 
 int /*<<< orphan*/  V1_INDIRECT_UNIQUENESS ; 
 int /*<<< orphan*/  V1_SD_UNIQUENESS ; 

__attribute__((used)) static inline __u32 type2uniqueness(int type)
{
	switch (type) {
	case TYPE_STAT_DATA:
		return V1_SD_UNIQUENESS;
	case TYPE_INDIRECT:
		return V1_INDIRECT_UNIQUENESS;
	case TYPE_DIRECT:
		return V1_DIRECT_UNIQUENESS;
	case TYPE_DIRENTRY:
		return V1_DIRENTRY_UNIQUENESS;
	case TYPE_ANY:
	default:
		return V1_ANY_UNIQUENESS;
	}
}