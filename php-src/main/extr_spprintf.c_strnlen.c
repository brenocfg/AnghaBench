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
 char* memchr (char const*,char,size_t) ; 

__attribute__((used)) static size_t strnlen(const char *s, size_t maxlen) {
	char *r = memchr(s, '\0', maxlen);
	return r ? r-s : maxlen;
}