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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 size_t BIO_dgram_get_mtu_overhead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_get_wbio (int /*<<< orphan*/ *) ; 
 size_t dtls1_link_min_mtu () ; 

size_t dtls1_min_mtu(SSL *s)
{
    return dtls1_link_min_mtu() - BIO_dgram_get_mtu_overhead(SSL_get_wbio(s));
}