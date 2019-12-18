#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uchar ;
struct TYPE_3__ {char key; char* val; } ;
typedef  TYPE_1__ kv ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 char* getenv (char const*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static bool parsekvpair(kv *kvarr, char **envcpy, const char *cfgstr, uchar maxitems)
{
	int i = 0;
	char *nextkey;
	char *ptr = getenv(cfgstr);

	if (!ptr || !*ptr)
		return TRUE;

	*envcpy = strdup(ptr);
	ptr = *envcpy;
	nextkey = ptr;

	while (*ptr && i < maxitems) {
		if (ptr == nextkey) {
			kvarr[i].key = *ptr;
			if (*++ptr != ':')
				return FALSE;
			if (*++ptr == '\0')
				return FALSE;
			kvarr[i].val = ptr;
			++i;
		}

		if (*ptr == ';') {
			/* Remove trailing space */
			if (i > 0 && *(ptr - 1) == '/')
				*(ptr - 1) = '\0';

			*ptr = '\0';
			nextkey = ptr + 1;
		}

		++ptr;
	}

	if (i < maxitems) {
		if (*kvarr[i - 1].val == '\0')
			return FALSE;
		kvarr[i].key = '\0';
	}

	return TRUE;
}