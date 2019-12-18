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
typedef  union outputArgs {int dummy; } outputArgs ;
struct CodaFid {int dummy; } ;
struct TYPE_4__ {int flags; struct CodaFid VFid; } ;
struct TYPE_3__ {int /*<<< orphan*/  uid; } ;
union inputArgs {TYPE_2__ coda_close; TYPE_1__ ih; } ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_CLOSE ; 
 int SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPARG (int /*<<< orphan*/ ) ; 
 int coda_upcall (int /*<<< orphan*/ ,int,int*,union inputArgs*) ; 
 int /*<<< orphan*/  coda_vcp (struct super_block*) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  kvfree (union inputArgs*) ; 
 int /*<<< orphan*/  release ; 

int venus_close(struct super_block *sb, struct CodaFid *fid, int flags,
		kuid_t uid)
{
	union inputArgs *inp;
	union outputArgs *outp;
	int insize, outsize, error;
	
	insize = SIZE(release);
	UPARG(CODA_CLOSE);
	
	inp->ih.uid = from_kuid(&init_user_ns, uid);
        inp->coda_close.VFid = *fid;
        inp->coda_close.flags = flags;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	kvfree(inp);
        return error;
}