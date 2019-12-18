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
struct ovl_fh {int len; scalar_t__ magic; scalar_t__ version; int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int OVL_FH_FLAG_ALL ; 
 int OVL_FH_FLAG_ANY_ENDIAN ; 
 int OVL_FH_FLAG_BIG_ENDIAN ; 
 int OVL_FH_FLAG_CPU_ENDIAN ; 
 scalar_t__ OVL_FH_MAGIC ; 
 scalar_t__ OVL_FH_VERSION ; 

int ovl_check_fh_len(struct ovl_fh *fh, int fh_len)
{
	if (fh_len < sizeof(struct ovl_fh) || fh_len < fh->len)
		return -EINVAL;

	if (fh->magic != OVL_FH_MAGIC)
		return -EINVAL;

	/* Treat larger version and unknown flags as "origin unknown" */
	if (fh->version > OVL_FH_VERSION || fh->flags & ~OVL_FH_FLAG_ALL)
		return -ENODATA;

	/* Treat endianness mismatch as "origin unknown" */
	if (!(fh->flags & OVL_FH_FLAG_ANY_ENDIAN) &&
	    (fh->flags & OVL_FH_FLAG_BIG_ENDIAN) != OVL_FH_FLAG_CPU_ENDIAN)
		return -ENODATA;

	return 0;
}