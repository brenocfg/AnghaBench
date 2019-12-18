#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int amp; scalar_t__ debug; scalar_t__ msg; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ SRP_ARG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ BN_BITS ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SRP_check_known_gN_param (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_srp_N (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_srp_g (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ srp_Verify_N_and_g (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssl_srp_verify_param_cb(SSL *s, void *arg)
{
    SRP_ARG *srp_arg = (SRP_ARG *)arg;
    BIGNUM *N = NULL, *g = NULL;

    if (((N = SSL_get_srp_N(s)) == NULL) || ((g = SSL_get_srp_g(s)) == NULL))
        return 0;
    if (srp_arg->debug || srp_arg->msg || srp_arg->amp == 1) {
        BIO_printf(bio_err, "SRP parameters:\n");
        BIO_printf(bio_err, "\tN=");
        BN_print(bio_err, N);
        BIO_printf(bio_err, "\n\tg=");
        BN_print(bio_err, g);
        BIO_printf(bio_err, "\n");
    }

    if (SRP_check_known_gN_param(g, N))
        return 1;

    if (srp_arg->amp == 1) {
        if (srp_arg->debug)
            BIO_printf(bio_err,
                       "SRP param N and g are not known params, going to check deeper.\n");

        /*
         * The srp_moregroups is a real debugging feature. Implementors
         * should rather add the value to the known ones. The minimal size
         * has already been tested.
         */
        if (BN_num_bits(g) <= BN_BITS && srp_Verify_N_and_g(N, g))
            return 1;
    }
    BIO_printf(bio_err, "SRP param N and g rejected.\n");
    return 0;
}