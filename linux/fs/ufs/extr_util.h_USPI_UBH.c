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
struct ufs_buffer_head {int dummy; } ;
struct ufs_sb_private_info {struct ufs_buffer_head s_ubh; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ufs_buffer_head *USPI_UBH(struct ufs_sb_private_info *spi)
{
	return &spi->s_ubh;
}