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
struct knfsd_fh {int dummy; } ;

/* Variables and functions */
 int FILE_HASH_SIZE ; 
 int nfsd_fh_hashval (struct knfsd_fh*) ; 

__attribute__((used)) static unsigned int file_hashval(struct knfsd_fh *fh)
{
	return nfsd_fh_hashval(fh) & (FILE_HASH_SIZE - 1);
}