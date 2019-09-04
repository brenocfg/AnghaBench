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
typedef  int uint32_t ;

/* Variables and functions */
 int crc32 (int,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static uint32_t xattr_datum_hashkey(int xprefix, const char *xname, const char *xvalue, int xsize)
{
	int name_len = strlen(xname);

	return crc32(xprefix, xname, name_len) ^ crc32(xprefix, xvalue, xsize);
}