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
 int /*<<< orphan*/  close_port_share () ; 
 int /*<<< orphan*/  free_ssl_lib () ; 
 int /*<<< orphan*/  pkcs11_terminate () ; 
 int /*<<< orphan*/  show_tls_performance_stats () ; 

void
uninit_static(void)
{
    free_ssl_lib();

#ifdef ENABLE_PKCS11
    pkcs11_terminate();
#endif

#if PORT_SHARE
    close_port_share();
#endif

#if defined(MEASURE_TLS_HANDSHAKE_STATS)
    show_tls_performance_stats();
#endif
}