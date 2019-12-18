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
 int SSL_TLSEXT_ERR_NOACK ; 
 int SSL_TLSEXT_ERR_OK ; 
 char* SSL_get_servername (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_NAMETYPE_host_name ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int hostname_cb(SSL *s, int *al, void *arg)
{
    const char *hostname = SSL_get_servername(s, TLSEXT_NAMETYPE_host_name);

    if (hostname != NULL && strcmp(hostname, "goodhost") == 0)
        return  SSL_TLSEXT_ERR_OK;

    return SSL_TLSEXT_ERR_NOACK;
}