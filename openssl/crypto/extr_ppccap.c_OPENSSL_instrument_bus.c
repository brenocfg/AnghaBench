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
 size_t OPENSSL_instrument_bus_mfspr268 (unsigned int*,size_t) ; 
 size_t OPENSSL_instrument_bus_mftb (unsigned int*,size_t) ; 
 int OPENSSL_ppccap_P ; 
 int PPC_MFSPR268 ; 
 int PPC_MFTB ; 

size_t OPENSSL_instrument_bus(unsigned int *out, size_t cnt)
{
    if (OPENSSL_ppccap_P & PPC_MFTB)
        return OPENSSL_instrument_bus_mftb(out, cnt);
    else if (OPENSSL_ppccap_P & PPC_MFSPR268)
        return OPENSSL_instrument_bus_mfspr268(out, cnt);
    else
        return 0;
}