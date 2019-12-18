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
 int /*<<< orphan*/  pgtls_init_library (int,int) ; 

void
PQinitOpenSSL(int do_ssl, int do_crypto)
{
#ifdef USE_SSL
	pgtls_init_library(do_ssl, do_crypto);
#endif
}