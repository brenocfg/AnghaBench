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
struct nfs_pgio_mirror {unsigned int pg_bsize; scalar_t__ pg_recoalesce; scalar_t__ pg_base; scalar_t__ pg_count; scalar_t__ pg_bytes_written; int /*<<< orphan*/  pg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_pageio_mirror_init(struct nfs_pgio_mirror *mirror,
				   unsigned int bsize)
{
	INIT_LIST_HEAD(&mirror->pg_list);
	mirror->pg_bytes_written = 0;
	mirror->pg_count = 0;
	mirror->pg_bsize = bsize;
	mirror->pg_base = 0;
	mirror->pg_recoalesce = 0;
}