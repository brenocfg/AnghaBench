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
typedef  int u8 ;
struct amp_mgr {scalar_t__ handle; } ;

/* Variables and functions */

__attribute__((used)) static u8 __next_handle(struct amp_mgr *mgr)
{
	if (++mgr->handle == 0)
		mgr->handle = 1;

	return mgr->handle;
}