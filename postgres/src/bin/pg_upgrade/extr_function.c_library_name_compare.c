#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; int dbnum; } ;
typedef  TYPE_1__ LibraryInfo ;

/* Variables and functions */
 int strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
library_name_compare(const void *p1, const void *p2)
{
	const char *str1 = ((const LibraryInfo *) p1)->name;
	const char *str2 = ((const LibraryInfo *) p2)->name;
	int			slen1 = strlen(str1);
	int			slen2 = strlen(str2);
	int			cmp = strcmp(str1, str2);

	if (slen1 != slen2)
		return slen1 - slen2;
	if (cmp != 0)
		return cmp;
	else
		return ((const LibraryInfo *) p1)->dbnum -
			((const LibraryInfo *) p2)->dbnum;
}