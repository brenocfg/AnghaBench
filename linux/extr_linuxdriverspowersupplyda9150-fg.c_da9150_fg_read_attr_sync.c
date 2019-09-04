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
typedef  int /*<<< orphan*/  u32 ;
struct da9150_fg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  da9150_fg_read_attr (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9150_fg_read_sync_end (struct da9150_fg*) ; 
 int /*<<< orphan*/  da9150_fg_read_sync_start (struct da9150_fg*) ; 

__attribute__((used)) static u32 da9150_fg_read_attr_sync(struct da9150_fg *fg, u8 code, u8 size)
{
	u32 val;

	da9150_fg_read_sync_start(fg);
	val = da9150_fg_read_attr(fg, code, size);
	da9150_fg_read_sync_end(fg);

	return val;
}