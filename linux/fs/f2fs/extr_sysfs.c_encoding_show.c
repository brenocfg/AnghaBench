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
struct f2fs_sb_info {TYPE_1__* s_encoding; } ;
struct f2fs_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* charset; int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ f2fs_sb_has_casefold (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ssize_t encoding_show(struct f2fs_attr *a,
		struct f2fs_sb_info *sbi, char *buf)
{
#ifdef CONFIG_UNICODE
	if (f2fs_sb_has_casefold(sbi))
		return snprintf(buf, PAGE_SIZE, "%s (%d.%d.%d)\n",
			sbi->s_encoding->charset,
			(sbi->s_encoding->version >> 16) & 0xff,
			(sbi->s_encoding->version >> 8) & 0xff,
			sbi->s_encoding->version & 0xff);
#endif
	return snprintf(buf, PAGE_SIZE, "(none)");
}