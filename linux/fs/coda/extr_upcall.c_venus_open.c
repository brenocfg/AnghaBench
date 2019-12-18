#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct file* fh; } ;
union outputArgs {TYPE_1__ coda_open_by_fd; } ;
struct CodaFid {int dummy; } ;
struct TYPE_4__ {int flags; struct CodaFid VFid; } ;
union inputArgs {TYPE_2__ coda_open_by_fd; } ;
struct super_block {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_OPEN_BY_FD ; 
 int SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPARG (int /*<<< orphan*/ ) ; 
 int coda_upcall (int /*<<< orphan*/ ,int,int*,union inputArgs*) ; 
 int /*<<< orphan*/  coda_vcp (struct super_block*) ; 
 int /*<<< orphan*/  kvfree (union inputArgs*) ; 
 int /*<<< orphan*/  open_by_fd ; 

int venus_open(struct super_block *sb, struct CodaFid *fid,
		  int flags, struct file **fh)
{
        union inputArgs *inp;
        union outputArgs *outp;
        int insize, outsize, error;
       
	insize = SIZE(open_by_fd);
	UPARG(CODA_OPEN_BY_FD);

	inp->coda_open_by_fd.VFid = *fid;
	inp->coda_open_by_fd.flags = flags;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);
	if (!error)
		*fh = outp->coda_open_by_fd.fh;

	kvfree(inp);
	return error;
}