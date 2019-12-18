#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  master_key_length; scalar_t__ master_key; } ;
typedef  TYPE_1__ SSL_SESSION ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_DIGEST_PARAM_SSL3_MS ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void ssl3_digest_master_key_set_params(const SSL_SESSION *session,
                                       OSSL_PARAM params[])
{
    int n = 0;
    params[n++] = OSSL_PARAM_construct_octet_string(OSSL_DIGEST_PARAM_SSL3_MS,
                                                    (void *)session->master_key,
                                                    session->master_key_length);
    params[n++] = OSSL_PARAM_construct_end();
}