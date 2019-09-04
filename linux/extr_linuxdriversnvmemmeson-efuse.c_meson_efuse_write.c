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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  SM_EFUSE_WRITE ; 
 int meson_sm_call_write (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,unsigned int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_efuse_write(void *context, unsigned int offset,
			     void *val, size_t bytes)
{
	return meson_sm_call_write((u8 *)val, bytes, SM_EFUSE_WRITE, offset,
				   bytes, 0, 0, 0);
}