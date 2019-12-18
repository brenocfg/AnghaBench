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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int OPENSSL_ppccap_P ; 
 int /*<<< orphan*/  OPENSSL_rdtsc_mfspr268 () ; 
 int /*<<< orphan*/  OPENSSL_rdtsc_mftb () ; 
 int PPC_MFSPR268 ; 
 int PPC_MFTB ; 

uint32_t OPENSSL_rdtsc(void)
{
    if (OPENSSL_ppccap_P & PPC_MFTB)
        return OPENSSL_rdtsc_mftb();
    else if (OPENSSL_ppccap_P & PPC_MFSPR268)
        return OPENSSL_rdtsc_mfspr268();
    else
        return 0;
}