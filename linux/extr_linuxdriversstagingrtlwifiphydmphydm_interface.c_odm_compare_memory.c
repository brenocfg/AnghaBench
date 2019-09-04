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
typedef  int /*<<< orphan*/  u32 ;
struct phy_dm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (void*,void*,int /*<<< orphan*/ ) ; 

s32 odm_compare_memory(struct phy_dm_struct *dm, void *p_buf1, void *buf2,
		       u32 length)
{
	return memcmp(p_buf1, buf2, length);
}