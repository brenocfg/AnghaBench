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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xfs_dir2_sf_put_ino(
	struct xfs_dir2_sf_hdr	*hdr,
	uint8_t			*to,
	xfs_ino_t		ino)
{
	ASSERT((ino & 0xff00000000000000ULL) == 0);

	if (hdr->i8count)
		put_unaligned_be64(ino, to);
	else
		put_unaligned_be32(ino, to);
}