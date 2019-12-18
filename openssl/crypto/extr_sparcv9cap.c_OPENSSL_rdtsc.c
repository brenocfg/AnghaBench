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
 int* OPENSSL_sparcv9cap_P ; 
 int SPARCV9_TICK_PRIVILEGED ; 
 int /*<<< orphan*/  _sparcv9_rdtick () ; 
 int /*<<< orphan*/  gethrtime () ; 

uint32_t OPENSSL_rdtsc(void)
{
    if (OPENSSL_sparcv9cap_P[0] & SPARCV9_TICK_PRIVILEGED)
#if defined(__sun) && defined(__SVR4)
        return gethrtime();
#else
        return 0;
#endif
    else
        return _sparcv9_rdtick();
}