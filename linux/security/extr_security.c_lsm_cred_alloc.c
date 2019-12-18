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
struct cred {int /*<<< orphan*/ * security; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {scalar_t__ lbs_cred; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__ blob_sizes ; 
 int /*<<< orphan*/ * kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lsm_cred_alloc(struct cred *cred, gfp_t gfp)
{
	if (blob_sizes.lbs_cred == 0) {
		cred->security = NULL;
		return 0;
	}

	cred->security = kzalloc(blob_sizes.lbs_cred, gfp);
	if (cred->security == NULL)
		return -ENOMEM;
	return 0;
}