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
struct ica_rsa_modexpo {int inputdatalength; } ;

/* Variables and functions */
 unsigned int EINVAL ; 
 int MEX_1K ; 
 int MEX_2K ; 
 int MEX_4K ; 

unsigned int get_rsa_modex_fc(struct ica_rsa_modexpo *mex, int *fcode)
{

	if (!mex->inputdatalength)
		return -EINVAL;

	if (mex->inputdatalength <= 128)	/* 1024 bit */
		*fcode = MEX_1K;
	else if (mex->inputdatalength <= 256)	/* 2048 bit */
		*fcode = MEX_2K;
	else					/* 4096 bit */
		*fcode = MEX_4K;

	return 0;
}