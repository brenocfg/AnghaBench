#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct super_block {int dummy; } ;
struct TYPE_2__ {scalar_t__ utf8; } ;
struct msdos_sb_info {int /*<<< orphan*/  nls_io; TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAT_MAX_UNI_CHARS ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  UTF16_HOST_ENDIAN ; 
 int uni16_to_x8 (struct super_block*,unsigned char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int utf16s_to_utf8s (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static inline int fat_uni_to_x8(struct super_block *sb, const wchar_t *uni,
				unsigned char *buf, int size)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	if (sbi->options.utf8)
		return utf16s_to_utf8s(uni, FAT_MAX_UNI_CHARS,
				UTF16_HOST_ENDIAN, buf, size);
	else
		return uni16_to_x8(sb, buf, uni, size, sbi->nls_io);
}