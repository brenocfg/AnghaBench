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
struct nfs_fh {scalar_t__* data; } ;

/* Variables and functions */
 int FILE_NRHASH ; 
 int NFS2_FHSIZE ; 

__attribute__((used)) static inline unsigned int file_hash(struct nfs_fh *f)
{
	unsigned int tmp=0;
	int i;
	for (i=0; i<NFS2_FHSIZE;i++)
		tmp += f->data[i];
	return tmp & (FILE_NRHASH - 1);
}