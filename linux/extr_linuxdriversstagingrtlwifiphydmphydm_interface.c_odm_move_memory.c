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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

void odm_move_memory(struct phy_dm_struct *dm, void *p_dest, void *src,
		     u32 length)
{
	memcpy(p_dest, src, length);
}