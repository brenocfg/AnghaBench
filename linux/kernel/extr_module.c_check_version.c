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
struct module {int dummy; } ;
struct load_info {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */

__attribute__((used)) static inline int check_version(const struct load_info *info,
				const char *symname,
				struct module *mod,
				const s32 *crc)
{
	return 1;
}