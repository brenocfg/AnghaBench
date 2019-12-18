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
 unsigned char* charsets ; 
 scalar_t__ strcasecmp (unsigned char const*,char const*) ; 
 scalar_t__ strlen (unsigned char const*) ; 

__attribute__((used)) static int find_charset(const char *name)
{
	const unsigned char *s;
	for (s=charsets; *s<0xff && strcasecmp(s+1, name); s+=strlen(s)+1);
	return *s;
}