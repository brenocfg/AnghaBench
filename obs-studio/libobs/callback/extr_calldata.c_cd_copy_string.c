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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static inline void cd_copy_string(uint8_t **pos, const char *str, size_t len)
{
	if (!len)
		len = strlen(str) + 1;

	memcpy(*pos, &len, sizeof(size_t));
	*pos += sizeof(size_t);
	memcpy(*pos, str, len);
	*pos += len;
}