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
struct CodaFid {int dummy; } ;
struct TYPE_2__ {struct CodaFid VFid; } ;
union outputArgs {TYPE_1__ coda_root; } ;
typedef  union inputArgs {int dummy; } inputArgs ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_FREE (union inputArgs*,int) ; 
 int /*<<< orphan*/  CODA_ROOT ; 
 int SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPARG (int /*<<< orphan*/ ) ; 
 int coda_upcall (int /*<<< orphan*/ ,int,int*,union inputArgs*) ; 
 int /*<<< orphan*/  coda_vcp (struct super_block*) ; 
 int /*<<< orphan*/  root ; 

int venus_rootfid(struct super_block *sb, struct CodaFid *fidp)
{
        union inputArgs *inp;
        union outputArgs *outp;
        int insize, outsize, error;

        insize = SIZE(root);
        UPARG(CODA_ROOT);

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);
	if (!error)
		*fidp = outp->coda_root.VFid;

	CODA_FREE(inp, insize);
	return error;
}