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
struct nfs_pageio_descriptor {int pg_mirror_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static inline bool nfs_pgio_has_mirroring(struct nfs_pageio_descriptor *desc)
{
	WARN_ON_ONCE(desc->pg_mirror_count < 1);
	return desc->pg_mirror_count > 1;
}