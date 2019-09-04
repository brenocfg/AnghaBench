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
struct TYPE_2__ {char name_check; } ;
struct msdos_sb_info {int /*<<< orphan*/  nls_io; TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (unsigned char const*,unsigned char const*,int) ; 
 int /*<<< orphan*/  nls_strnicmp (int /*<<< orphan*/ ,unsigned char const*,unsigned char const*,int) ; 

__attribute__((used)) static inline int fat_name_match(struct msdos_sb_info *sbi,
				 const unsigned char *a, int a_len,
				 const unsigned char *b, int b_len)
{
	if (a_len != b_len)
		return 0;

	if (sbi->options.name_check != 's')
		return !nls_strnicmp(sbi->nls_io, a, b, a_len);
	else
		return !memcmp(a, b, a_len);
}