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
 int MAXPATHLEN ; 
 char const* ext ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static char *mkdbname(const char *fn, int strip) {
	char *buf = NULL;
	int fnlen, extlen;
	if (strip) {
		const char *p;
		if ((p = strrchr (fn, '/')) != NULL) {
			fn = ++p;
		}
	}
	fnlen = strlen (fn);
	extlen = strlen (ext);
	if (fnlen + extlen + 1 > MAXPATHLEN) {
		return NULL;
	}
	buf = malloc (fnlen + extlen + 1);
	if (buf) {
		memcpy (buf, fn, fnlen);
		memcpy (buf+fnlen, ext, extlen);
		buf[fnlen+extlen] = 0;
	}
	return buf;
}