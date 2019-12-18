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
 int /*<<< orphan*/  crypto_uninit_lib () ; 
 int /*<<< orphan*/  prng_uninit () ; 
 int /*<<< orphan*/  tls_free_lib () ; 

void
free_ssl_lib(void)
{
    crypto_uninit_lib();
    prng_uninit();

    tls_free_lib();
}