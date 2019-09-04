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
 int json_len (TYPE_1__*) ; 
 char* realloc (char*,unsigned int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static void addfield(char *map, char **dst, const char *sep,
		     const char *a, jsmntok_t *bt)
{
	unsigned int len = strlen(a) + 1 + strlen(sep);
	int olen = *dst ? strlen(*dst) : 0;
	int blen = bt ? json_len(bt) : 0;
	char *out;

	out = realloc(*dst, len + olen + blen);
	if (!out) {
		/* Don't add field in this case */
		return;
	}
	*dst = out;

	if (!olen)
		*(*dst) = 0;
	else
		strcat(*dst, sep);
	strcat(*dst, a);
	if (bt)
		strncat(*dst, map + bt->start, blen);
}