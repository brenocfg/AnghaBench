#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
typedef  size_t grant_ref_t ;
struct TYPE_4__ {TYPE_1__* v1; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int GTF_reading ; 
 int GTF_writing ; 
 TYPE_2__ gnttab_shared ; 
 int sync_cmpxchg (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gnttab_end_foreign_access_ref_v1(grant_ref_t ref, int readonly)
{
	u16 flags, nflags;
	u16 *pflags;

	pflags = &gnttab_shared.v1[ref].flags;
	nflags = *pflags;
	do {
		flags = nflags;
		if (flags & (GTF_reading|GTF_writing))
			return 0;
	} while ((nflags = sync_cmpxchg(pflags, flags, 0)) != flags);

	return 1;
}