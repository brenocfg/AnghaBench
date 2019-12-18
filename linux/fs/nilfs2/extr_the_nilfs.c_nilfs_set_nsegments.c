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
struct the_nilfs {unsigned long ns_nsegments; int /*<<< orphan*/  ns_nrsvsegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_nrsvsegs (struct the_nilfs*,unsigned long) ; 

void nilfs_set_nsegments(struct the_nilfs *nilfs, unsigned long nsegs)
{
	nilfs->ns_nsegments = nsegs;
	nilfs->ns_nrsvsegs = nilfs_nrsvsegs(nilfs, nsegs);
}