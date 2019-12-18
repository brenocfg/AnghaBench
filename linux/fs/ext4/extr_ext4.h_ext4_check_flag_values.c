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

/* Variables and functions */
 int /*<<< orphan*/  APPEND ; 
 int /*<<< orphan*/  CHECK_FLAG_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPR ; 
 int /*<<< orphan*/  COMPRBLK ; 
 int /*<<< orphan*/  DIRSYNC ; 
 int /*<<< orphan*/  DIRTY ; 
 int /*<<< orphan*/  EA_INODE ; 
 int /*<<< orphan*/  ENCRYPT ; 
 int /*<<< orphan*/  EOFBLOCKS ; 
 int /*<<< orphan*/  EXTENTS ; 
 int /*<<< orphan*/  HUGE_FILE ; 
 int /*<<< orphan*/  IMAGIC ; 
 int /*<<< orphan*/  IMMUTABLE ; 
 int /*<<< orphan*/  INDEX ; 
 int /*<<< orphan*/  INLINE_DATA ; 
 int /*<<< orphan*/  JOURNAL_DATA ; 
 int /*<<< orphan*/  NOATIME ; 
 int /*<<< orphan*/  NOCOMPR ; 
 int /*<<< orphan*/  NODUMP ; 
 int /*<<< orphan*/  NOTAIL ; 
 int /*<<< orphan*/  PROJINHERIT ; 
 int /*<<< orphan*/  RESERVED ; 
 int /*<<< orphan*/  SECRM ; 
 int /*<<< orphan*/  SYNC ; 
 int /*<<< orphan*/  TOPDIR ; 
 int /*<<< orphan*/  UNRM ; 
 int /*<<< orphan*/  VERITY ; 

__attribute__((used)) static inline void ext4_check_flag_values(void)
{
	CHECK_FLAG_VALUE(SECRM);
	CHECK_FLAG_VALUE(UNRM);
	CHECK_FLAG_VALUE(COMPR);
	CHECK_FLAG_VALUE(SYNC);
	CHECK_FLAG_VALUE(IMMUTABLE);
	CHECK_FLAG_VALUE(APPEND);
	CHECK_FLAG_VALUE(NODUMP);
	CHECK_FLAG_VALUE(NOATIME);
	CHECK_FLAG_VALUE(DIRTY);
	CHECK_FLAG_VALUE(COMPRBLK);
	CHECK_FLAG_VALUE(NOCOMPR);
	CHECK_FLAG_VALUE(ENCRYPT);
	CHECK_FLAG_VALUE(INDEX);
	CHECK_FLAG_VALUE(IMAGIC);
	CHECK_FLAG_VALUE(JOURNAL_DATA);
	CHECK_FLAG_VALUE(NOTAIL);
	CHECK_FLAG_VALUE(DIRSYNC);
	CHECK_FLAG_VALUE(TOPDIR);
	CHECK_FLAG_VALUE(HUGE_FILE);
	CHECK_FLAG_VALUE(EXTENTS);
	CHECK_FLAG_VALUE(VERITY);
	CHECK_FLAG_VALUE(EA_INODE);
	CHECK_FLAG_VALUE(EOFBLOCKS);
	CHECK_FLAG_VALUE(INLINE_DATA);
	CHECK_FLAG_VALUE(PROJINHERIT);
	CHECK_FLAG_VALUE(RESERVED);
}