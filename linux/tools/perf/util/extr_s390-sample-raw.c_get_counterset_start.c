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

/* Variables and functions */
#define  CPUMF_CTR_SET_BASIC 132 
#define  CPUMF_CTR_SET_CRYPTO 131 
#define  CPUMF_CTR_SET_EXT 130 
#define  CPUMF_CTR_SET_MT_DIAG 129 
#define  CPUMF_CTR_SET_USER 128 

__attribute__((used)) static int get_counterset_start(int setnr)
{
	switch (setnr) {
	case CPUMF_CTR_SET_BASIC:		/* Basic counter set */
		return 0;
	case CPUMF_CTR_SET_USER:		/* Problem state counter set */
		return 32;
	case CPUMF_CTR_SET_CRYPTO:		/* Crypto counter set */
		return 64;
	case CPUMF_CTR_SET_EXT:			/* Extended counter set */
		return 128;
	case CPUMF_CTR_SET_MT_DIAG:		/* Diagnostic counter set */
		return 448;
	default:
		return -1;
	}
}