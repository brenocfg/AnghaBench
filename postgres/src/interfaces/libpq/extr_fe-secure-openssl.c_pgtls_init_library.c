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
 int pq_init_crypto_lib ; 
 int pq_init_ssl_lib ; 
 scalar_t__ ssl_open_connections ; 

void
pgtls_init_library(bool do_ssl, int do_crypto)
{
#ifdef ENABLE_THREAD_SAFETY

	/*
	 * Disallow changing the flags while we have open connections, else we'd
	 * get completely confused.
	 */
	if (ssl_open_connections != 0)
		return;
#endif

	pq_init_ssl_lib = do_ssl;
	pq_init_crypto_lib = do_crypto;
}