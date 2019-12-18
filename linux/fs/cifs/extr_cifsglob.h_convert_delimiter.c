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
 char* strchr (char*,char) ; 

__attribute__((used)) static inline void
convert_delimiter(char *path, char delim)
{
	char old_delim, *pos;

	if (delim == '/')
		old_delim = '\\';
	else
		old_delim = '/';

	pos = path;
	while ((pos = strchr(pos, old_delim)))
		*pos = delim;
}