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
struct WD33C93_hostdata {int /*<<< orphan*/ * sync_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  SS_UNSET ; 

__attribute__((used)) static inline void set_resync ( struct WD33C93_hostdata *hd, int mask )
{
	int i;
	for (i = 0; i < 8; i++)
		if (mask & (1 << i))
			hd->sync_stat[i] = SS_UNSET;
}