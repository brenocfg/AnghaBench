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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ufs_sb_private_info {int /*<<< orphan*/  s_fpg; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 ufs_dtogd(struct ufs_sb_private_info * uspi, u64 b)
{
	return do_div(b, uspi->s_fpg);
}