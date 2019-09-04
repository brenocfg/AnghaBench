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
struct ubifs_info {int orph_lebs; int leb_size; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int UBIFS_ORPH_NODE_SZ ; 

__attribute__((used)) static int tot_avail_orphs(struct ubifs_info *c)
{
	int avail_lebs, avail;

	avail_lebs = c->orph_lebs;
	avail = avail_lebs *
	       ((c->leb_size - UBIFS_ORPH_NODE_SZ) / sizeof(__le64));
	return avail / 2;
}