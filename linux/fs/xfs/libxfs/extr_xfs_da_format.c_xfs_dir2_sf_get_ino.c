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
typedef  int xfs_ino_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct xfs_dir2_sf_hdr {scalar_t__ i8count; } ;

/* Variables and functions */
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 int get_unaligned_be64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xfs_ino_t
xfs_dir2_sf_get_ino(
	struct xfs_dir2_sf_hdr	*hdr,
	uint8_t			*from)
{
	if (hdr->i8count)
		return get_unaligned_be64(from) & 0x00ffffffffffffffULL;
	else
		return get_unaligned_be32(from);
}