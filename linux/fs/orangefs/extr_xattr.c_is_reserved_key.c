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
 int /*<<< orphan*/  SYSTEM_ORANGEFS_KEY ; 
 size_t SYSTEM_ORANGEFS_KEY_LEN ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int is_reserved_key(const char *key, size_t size)
{

	if (size < SYSTEM_ORANGEFS_KEY_LEN)
		return 1;

	return strncmp(key, SYSTEM_ORANGEFS_KEY, SYSTEM_ORANGEFS_KEY_LEN) ?  1 : 0;
}