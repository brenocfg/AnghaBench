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
typedef  int /*<<< orphan*/  custom_ext_parse_cb ;
typedef  int /*<<< orphan*/  custom_ext_free_cb ;
typedef  int /*<<< orphan*/  custom_ext_add_cb ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ENDPOINT_SERVER ; 
 int SSL_EXT_CLIENT_HELLO ; 
 int SSL_EXT_IGNORE_ON_RESUMPTION ; 
 int SSL_EXT_TLS1_2_AND_BELOW_ONLY ; 
 int SSL_EXT_TLS1_2_SERVER_HELLO ; 
 int add_old_custom_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*) ; 

int SSL_CTX_add_server_custom_ext(SSL_CTX *ctx, unsigned int ext_type,
                                  custom_ext_add_cb add_cb,
                                  custom_ext_free_cb free_cb,
                                  void *add_arg,
                                  custom_ext_parse_cb parse_cb, void *parse_arg)
{
    return add_old_custom_ext(ctx, ENDPOINT_SERVER, ext_type,
                              SSL_EXT_TLS1_2_AND_BELOW_ONLY
                              | SSL_EXT_CLIENT_HELLO
                              | SSL_EXT_TLS1_2_SERVER_HELLO
                              | SSL_EXT_IGNORE_ON_RESUMPTION,
                              add_cb, free_cb, add_arg, parse_cb, parse_arg);
}