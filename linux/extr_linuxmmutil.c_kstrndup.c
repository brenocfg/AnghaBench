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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 char* kmalloc_track_caller (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strnlen (char const*,size_t) ; 

char *kstrndup(const char *s, size_t max, gfp_t gfp)
{
	size_t len;
	char *buf;

	if (!s)
		return NULL;

	len = strnlen(s, max);
	buf = kmalloc_track_caller(len+1, gfp);
	if (buf) {
		memcpy(buf, s, len);
		buf[len] = '\0';
	}
	return buf;
}