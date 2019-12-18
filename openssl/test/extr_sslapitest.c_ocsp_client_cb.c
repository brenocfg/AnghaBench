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
 size_t SSL_get_tlsext_status_ocsp_resp (int /*<<< orphan*/ *,unsigned char const**) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,size_t,unsigned char const*,size_t) ; 
 int ocsp_client_called ; 
 int /*<<< orphan*/  orespder ; 

__attribute__((used)) static int ocsp_client_cb(SSL *s, void *arg)
{
    int *argi = (int *)arg;
    const unsigned char *respderin;
    size_t len;

    if (*argi != 1 && *argi != 2)
        return 0;

    len = SSL_get_tlsext_status_ocsp_resp(s, &respderin);
    if (!TEST_mem_eq(orespder, len, respderin, len))
        return 0;

    ocsp_client_called = 1;
    return 1;
}