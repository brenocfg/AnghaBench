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
struct coda_vattr {int dummy; } ;
struct TYPE_4__ {struct coda_vattr attr; } ;
union outputArgs {TYPE_2__ coda_getattr; } ;
struct CodaFid {int dummy; } ;
struct TYPE_3__ {struct CodaFid VFid; } ;
union inputArgs {TYPE_1__ coda_getattr; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_FREE (union inputArgs*,int) ; 
 int /*<<< orphan*/  CODA_GETATTR ; 
 int SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPARG (int /*<<< orphan*/ ) ; 
 int coda_upcall (int /*<<< orphan*/ ,int,int*,union inputArgs*) ; 
 int /*<<< orphan*/  coda_vcp (struct super_block*) ; 
 int /*<<< orphan*/  getattr ; 

int venus_getattr(struct super_block *sb, struct CodaFid *fid, 
		     struct coda_vattr *attr) 
{
        union inputArgs *inp;
        union outputArgs *outp;
        int insize, outsize, error;

        insize = SIZE(getattr); 
	UPARG(CODA_GETATTR);
        inp->coda_getattr.VFid = *fid;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);
	if (!error)
		*attr = outp->coda_getattr.attr;

	CODA_FREE(inp, insize);
        return error;
}