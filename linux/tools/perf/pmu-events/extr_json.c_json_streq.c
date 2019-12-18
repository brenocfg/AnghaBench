#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int start; } ;
typedef  TYPE_1__ jsmntok_t ;

/* Variables and functions */
 unsigned int json_len (TYPE_1__*) ; 
 unsigned int strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char const*,unsigned int) ; 

int json_streq(char *map, jsmntok_t *t, const char *s)
{
	unsigned len = json_len(t);
	return len == strlen(s) && !strncasecmp(map + t->start, s, len);
}