#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rand_tmp ;
struct TYPE_4__ {int /*<<< orphan*/ * N; int /*<<< orphan*/ * g; } ;
typedef  TYPE_1__ SRP_gN ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int RANDOM_SIZE ; 
 int /*<<< orphan*/  RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/ * SRP_Calc_A (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SRP_Calc_B (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SRP_Calc_client_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SRP_Calc_server_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SRP_Calc_u (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SRP_Calc_x (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  SRP_Verify_A_mod_N (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRP_Verify_B_mod_N (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRP_create_verifier_BN (char const*,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* SRP_get_default_gN (char*) ; 
 int /*<<< orphan*/  TEST_BN_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_BN_ne_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__ const*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_output_bignum (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_srp(const char *username, const char *client_pass,
                   const char *server_pass)
{
    int ret = 0;
    BIGNUM *s = NULL;
    BIGNUM *v = NULL;
    BIGNUM *a = NULL;
    BIGNUM *b = NULL;
    BIGNUM *u = NULL;
    BIGNUM *x = NULL;
    BIGNUM *Apub = NULL;
    BIGNUM *Bpub = NULL;
    BIGNUM *Kclient = NULL;
    BIGNUM *Kserver = NULL;
    unsigned char rand_tmp[RANDOM_SIZE];
    /* use builtin 1024-bit params */
    const SRP_gN *GN;

    if (!TEST_ptr(GN = SRP_get_default_gN("1024")))
        return 0;

    /* Set up server's password entry */
    if (!TEST_true(SRP_create_verifier_BN(username, server_pass,
                                          &s, &v, GN->N, GN->g)))
        goto end;

    test_output_bignum("N", GN->N);
    test_output_bignum("g", GN->g);
    test_output_bignum("Salt", s);
    test_output_bignum("Verifier", v);

    /* Server random */
    RAND_bytes(rand_tmp, sizeof(rand_tmp));
    b = BN_bin2bn(rand_tmp, sizeof(rand_tmp), NULL);
    if (!TEST_BN_ne_zero(b))
        goto end;
    test_output_bignum("b", b);

    /* Server's first message */
    Bpub = SRP_Calc_B(b, GN->N, GN->g, v);
    test_output_bignum("B", Bpub);

    if (!TEST_true(SRP_Verify_B_mod_N(Bpub, GN->N)))
        goto end;

    /* Client random */
    RAND_bytes(rand_tmp, sizeof(rand_tmp));
    a = BN_bin2bn(rand_tmp, sizeof(rand_tmp), NULL);
    if (!TEST_BN_ne_zero(a))
        goto end;
    test_output_bignum("a", a);

    /* Client's response */
    Apub = SRP_Calc_A(a, GN->N, GN->g);
    test_output_bignum("A", Apub);

    if (!TEST_true(SRP_Verify_A_mod_N(Apub, GN->N)))
        goto end;

    /* Both sides calculate u */
    u = SRP_Calc_u(Apub, Bpub, GN->N);

    /* Client's key */
    x = SRP_Calc_x(s, username, client_pass);
    Kclient = SRP_Calc_client_key(GN->N, Bpub, GN->g, x, a, u);
    test_output_bignum("Client's key", Kclient);

    /* Server's key */
    Kserver = SRP_Calc_server_key(Apub, v, u, b, GN->N);
    test_output_bignum("Server's key", Kserver);

    if (!TEST_BN_eq(Kclient, Kserver))
        goto end;

    ret = 1;

end:
    BN_clear_free(Kclient);
    BN_clear_free(Kserver);
    BN_clear_free(x);
    BN_free(u);
    BN_free(Apub);
    BN_clear_free(a);
    BN_free(Bpub);
    BN_clear_free(b);
    BN_free(s);
    BN_clear_free(v);

    return ret;
}