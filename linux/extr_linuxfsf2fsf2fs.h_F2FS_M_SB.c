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
struct f2fs_sb_info {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_I_SB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct f2fs_sb_info *F2FS_M_SB(struct address_space *mapping)
{
	return F2FS_I_SB(mapping->host);
}