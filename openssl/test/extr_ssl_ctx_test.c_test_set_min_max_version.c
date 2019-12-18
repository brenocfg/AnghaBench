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
struct TYPE_3__ {int /*<<< orphan*/  expected_max; int /*<<< orphan*/  expected_min; int /*<<< orphan*/  max_ok; int /*<<< orphan*/  max_version; int /*<<< orphan*/  min_ok; int /*<<< orphan*/  min_version; } ;
typedef  TYPE_1__ version_test ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_get_max_proto_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_get_min_proto_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_max_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_min_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_max_proto_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_min_proto_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_max_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_min_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 TYPE_1__* version_testdata ; 

__attribute__((used)) static int test_set_min_max_version(int idx_tst)
{
    SSL_CTX *ctx = NULL;
    SSL *ssl = NULL;
    int testresult = 0;
    version_test t = version_testdata[idx_tst];

    ctx = SSL_CTX_new(TLS_server_method());
    if (ctx == NULL)
        goto end;

    ssl = SSL_new(ctx);
    if (ssl == NULL)
        goto end;

    if (!TEST_int_eq(SSL_CTX_set_min_proto_version(ctx, t.min_version), t.min_ok))
        goto end;
    if (!TEST_int_eq(SSL_CTX_set_max_proto_version(ctx, t.max_version), t.max_ok))
        goto end;
    if (!TEST_int_eq(SSL_CTX_get_min_proto_version(ctx), t.expected_min))
        goto end;
    if (!TEST_int_eq(SSL_CTX_get_max_proto_version(ctx), t.expected_max))
        goto end;

    if (!TEST_int_eq(SSL_set_min_proto_version(ssl, t.min_version), t.min_ok))
        goto end;
    if (!TEST_int_eq(SSL_set_max_proto_version(ssl, t.max_version), t.max_ok))
        goto end;
    if (!TEST_int_eq(SSL_get_min_proto_version(ssl), t.expected_min))
        goto end;
    if (!TEST_int_eq(SSL_get_max_proto_version(ssl), t.expected_max))
        goto end;

    testresult = 1;

  end:
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    return testresult;
}