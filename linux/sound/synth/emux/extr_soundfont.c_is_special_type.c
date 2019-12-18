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

/* Variables and functions */
 int SNDRV_SFNT_PAT_TYPE_GUS ; 
 int SNDRV_SFNT_PAT_TYPE_MAP ; 

__attribute__((used)) static inline int
is_special_type(int type)
{
	type &= 0x0f;
	return (type == SNDRV_SFNT_PAT_TYPE_GUS ||
		type == SNDRV_SFNT_PAT_TYPE_MAP);
}