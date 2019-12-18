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
 int /*<<< orphan*/  smart_str_append_unsigned (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  smart_str_appendl (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static inline void php_var_serialize_string(smart_str *buf, char *str, size_t len) /* {{{ */
{
	smart_str_appendl(buf, "s:", 2);
	smart_str_append_unsigned(buf, len);
	smart_str_appendl(buf, ":\"", 2);
	smart_str_appendl(buf, str, len);
	smart_str_appendl(buf, "\";", 2);
}