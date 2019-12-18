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
 scalar_t__ datadir_source ; 
 char* libpqGetFile (char const*,size_t*) ; 
 char* slurpFile (scalar_t__,char const*,size_t*) ; 

char *
fetchFile(const char *filename, size_t *filesize)
{
	if (datadir_source)
		return slurpFile(datadir_source, filename, filesize);
	else
		return libpqGetFile(filename, filesize);
}