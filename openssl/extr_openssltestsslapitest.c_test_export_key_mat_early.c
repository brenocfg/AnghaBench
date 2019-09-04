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
typedef  int /*<<< orphan*/  skeymat2 ;
typedef  int /*<<< orphan*/  skeymat1 ;
typedef  int /*<<< orphan*/  label ;
typedef  int /*<<< orphan*/  context ;
typedef  int /*<<< orphan*/  ckeymat2 ;
typedef  int /*<<< orphan*/  ckeymat1 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int SSL_EARLY_DATA_ACCEPTED ; 
 int SSL_READ_EARLY_DATA_ERROR ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_export_keying_material_early (int /*<<< orphan*/ *,unsigned char*,int,char const*,int,unsigned char const*,int) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_early_data_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_read_early_data (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  SSL_write_early_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_mem_ne (unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clientpsk ; 
 int /*<<< orphan*/ * serverpsk ; 
 int /*<<< orphan*/  setupearly_data_test (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int test_export_key_mat_early(int idx)
{
    static const char label[] = "test label";
    static const unsigned char context[] = "context";
    int testresult = 0;
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    SSL_SESSION *sess = NULL;
    const unsigned char *emptycontext = NULL;
    unsigned char ckeymat1[80], ckeymat2[80];
    unsigned char skeymat1[80], skeymat2[80];
    unsigned char buf[1];
    size_t readbytes, written;

    if (!TEST_true(setupearly_data_test(&cctx, &sctx, &clientssl, &serverssl,
                                        &sess, idx)))
        goto end;

    /* Here writing 0 length early data is enough. */
    if (!TEST_true(SSL_write_early_data(clientssl, NULL, 0, &written))
            || !TEST_int_eq(SSL_read_early_data(serverssl, buf, sizeof(buf),
                                                &readbytes),
                            SSL_READ_EARLY_DATA_ERROR)
            || !TEST_int_eq(SSL_get_early_data_status(serverssl),
                            SSL_EARLY_DATA_ACCEPTED))
        goto end;

    if (!TEST_int_eq(SSL_export_keying_material_early(
                     clientssl, ckeymat1, sizeof(ckeymat1), label,
                     sizeof(label) - 1, context, sizeof(context) - 1), 1)
            || !TEST_int_eq(SSL_export_keying_material_early(
                            clientssl, ckeymat2, sizeof(ckeymat2), label,
                            sizeof(label) - 1, emptycontext, 0), 1)
            || !TEST_int_eq(SSL_export_keying_material_early(
                            serverssl, skeymat1, sizeof(skeymat1), label,
                            sizeof(label) - 1, context, sizeof(context) - 1), 1)
            || !TEST_int_eq(SSL_export_keying_material_early(
                            serverssl, skeymat2, sizeof(skeymat2), label,
                            sizeof(label) - 1, emptycontext, 0), 1)
               /*
                * Check that both sides created the same key material with the
                * same context.
                */
            || !TEST_mem_eq(ckeymat1, sizeof(ckeymat1), skeymat1,
                            sizeof(skeymat1))
               /*
                * Check that both sides created the same key material with an
                * empty context.
                */
            || !TEST_mem_eq(ckeymat2, sizeof(ckeymat2), skeymat2,
                            sizeof(skeymat2))
               /* Different contexts should produce different results */
            || !TEST_mem_ne(ckeymat1, sizeof(ckeymat1), ckeymat2,
                            sizeof(ckeymat2)))
        goto end;

    testresult = 1;

 end:
    SSL_SESSION_free(sess);
    SSL_SESSION_free(clientpsk);
    SSL_SESSION_free(serverpsk);
    clientpsk = serverpsk = NULL;
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}