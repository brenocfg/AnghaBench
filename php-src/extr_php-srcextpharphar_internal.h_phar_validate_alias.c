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
 scalar_t__ memchr (char const*,char,size_t) ; 

__attribute__((used)) static inline int phar_validate_alias(const char *alias, size_t alias_len) /* {{{ */
{
	return !(memchr(alias, '/', alias_len) || memchr(alias, '\\', alias_len) || memchr(alias, ':', alias_len) ||
		memchr(alias, ';', alias_len) || memchr(alias, '\n', alias_len) || memchr(alias, '\r', alias_len));
}