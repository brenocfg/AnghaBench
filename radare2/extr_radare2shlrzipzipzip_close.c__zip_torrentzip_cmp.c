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
struct zip_filelist {char* name; } ;

/* Variables and functions */
 int __strcasecmp (char const*,char const*) ; 

__attribute__((used)) static int
_zip_torrentzip_cmp(const void *a, const void *b)
{
    const char *aname = ((const struct zip_filelist *)a)->name;
    const char *bname = ((const struct zip_filelist *)b)->name;

    if (aname == NULL)
	return (bname != NULL) * -1;
    else if (bname == NULL)
	return 1;

    return __strcasecmp(aname, bname);
}