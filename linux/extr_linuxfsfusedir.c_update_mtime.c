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
 unsigned int ATTR_FILE ; 
 unsigned int ATTR_MTIME_SET ; 
 unsigned int ATTR_OPEN ; 
 unsigned int ATTR_SIZE ; 

__attribute__((used)) static bool update_mtime(unsigned ivalid, bool trust_local_mtime)
{
	/* Always update if mtime is explicitly set  */
	if (ivalid & ATTR_MTIME_SET)
		return true;

	/* Or if kernel i_mtime is the official one */
	if (trust_local_mtime)
		return true;

	/* If it's an open(O_TRUNC) or an ftruncate(), don't update */
	if ((ivalid & ATTR_SIZE) && (ivalid & (ATTR_OPEN | ATTR_FILE)))
		return false;

	/* In all other cases update */
	return true;
}