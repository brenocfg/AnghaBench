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
struct erofs_sb_info {int islotbits; int /*<<< orphan*/  meta_blkaddr; } ;
typedef  scalar_t__ erofs_off_t ;
typedef  int erofs_nid_t ;

/* Variables and functions */
 scalar_t__ blknr_to_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline erofs_off_t iloc(struct erofs_sb_info *sbi, erofs_nid_t nid)
{
	return blknr_to_addr(sbi->meta_blkaddr) + (nid << sbi->islotbits);
}