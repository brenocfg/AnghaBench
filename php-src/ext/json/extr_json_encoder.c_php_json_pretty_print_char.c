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
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 int PHP_JSON_PRETTY_PRINT ; 
 int /*<<< orphan*/  smart_str_appendc (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static inline void php_json_pretty_print_char(smart_str *buf, int options, char c) /* {{{ */
{
	if (options & PHP_JSON_PRETTY_PRINT) {
		smart_str_appendc(buf, c);
	}
}