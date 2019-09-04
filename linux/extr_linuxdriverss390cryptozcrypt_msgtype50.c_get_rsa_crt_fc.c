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
struct ica_rsa_modexpo_crt {int inputdatalength; } ;

/* Variables and functions */
 int CRT_1K ; 
 int CRT_2K ; 
 int CRT_4K ; 
 unsigned int EINVAL ; 

unsigned int get_rsa_crt_fc(struct ica_rsa_modexpo_crt *crt, int *fcode)
{

	if (!crt->inputdatalength)
		return -EINVAL;

	if (crt->inputdatalength <= 128)	/* 1024 bit */
		*fcode = CRT_1K;
	else if (crt->inputdatalength <= 256)	/* 2048 bit */
		*fcode = CRT_2K;
	else					/* 4096 bit */
		*fcode = CRT_4K;

	return 0;
}