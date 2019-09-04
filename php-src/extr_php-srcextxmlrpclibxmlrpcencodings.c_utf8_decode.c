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
 char* convert (char const*,int,int*,char*,char const*) ; 

char* utf8_decode(const char *s, int len, int *newlen, const char* encoding)
{
   return convert(s, len, newlen, "UTF-8", encoding);
}