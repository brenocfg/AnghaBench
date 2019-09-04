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
struct free_segmap_info {int /*<<< orphan*/  free_sections; int /*<<< orphan*/  free_secmap; int /*<<< orphan*/  free_segments; int /*<<< orphan*/  free_segmap; } ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 struct free_segmap_info* FREE_I (struct f2fs_sb_info*) ; 
 unsigned int GET_SEC_FROM_SEG (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __set_inuse(struct f2fs_sb_info *sbi,
		unsigned int segno)
{
	struct free_segmap_info *free_i = FREE_I(sbi);
	unsigned int secno = GET_SEC_FROM_SEG(sbi, segno);

	set_bit(segno, free_i->free_segmap);
	free_i->free_segments--;
	if (!test_and_set_bit(secno, free_i->free_secmap))
		free_i->free_sections--;
}