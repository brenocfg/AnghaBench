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
 size_t strarrays__scnprintf (int /*<<< orphan*/ *,char*,size_t,char*,int,int) ; 
 int /*<<< orphan*/  strarrays__x86_arch_prctl_codes ; 

__attribute__((used)) static size_t x86_arch_prctl__scnprintf_code(int option, char *bf, size_t size, bool show_prefix)
{
	return strarrays__scnprintf(&strarrays__x86_arch_prctl_codes, bf, size, "%#x", show_prefix, option);
}