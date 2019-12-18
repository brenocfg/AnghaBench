#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ edid_max_size; } ;
struct mdev_state {char* edid_blob; TYPE_1__ edid_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 

__attribute__((used)) static void handle_edid_blob(struct mdev_state *mdev_state, u16 offset,
			     char *buf, u32 count, bool is_write)
{
	if (offset + count > mdev_state->edid_regs.edid_max_size)
		return;
	if (is_write)
		memcpy(mdev_state->edid_blob + offset, buf, count);
	else
		memcpy(buf, mdev_state->edid_blob + offset, count);
}