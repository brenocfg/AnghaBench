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
 scalar_t__* CLIR_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (size_t,int) ; 
 scalar_t__ VCWD_POPEN (scalar_t__*,char*) ; 
 size_t fwrite (char const*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pager ; 
 scalar_t__ pager_pipe ; 
 int /*<<< orphan*/  prompt_str ; 
 int /*<<< orphan*/  smart_str_appendl (scalar_t__*,char const*,size_t) ; 

__attribute__((used)) static size_t readline_shell_write(const char *str, size_t str_length) /* {{{ */
{
	if (CLIR_G(prompt_str)) {
		smart_str_appendl(CLIR_G(prompt_str), str, str_length);
		return str_length;
	}

	if (CLIR_G(pager) && *CLIR_G(pager) && !pager_pipe) {
		pager_pipe = VCWD_POPEN(CLIR_G(pager), "w");
	}
	if (pager_pipe) {
		return fwrite(str, 1, MIN(str_length, 16384), pager_pipe);
	}

	return -1;
}