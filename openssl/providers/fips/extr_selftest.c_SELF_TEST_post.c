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
struct TYPE_3__ {int /*<<< orphan*/  (* bio_free_cb ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  libctx; int /*<<< orphan*/  bio_read_ex_cb; int /*<<< orphan*/ * indicator_data; int /*<<< orphan*/ * (* bio_new_buffer_cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * indicator_checksum_data; int /*<<< orphan*/  module_filename; int /*<<< orphan*/ * (* bio_new_file_cb ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/ * module_checksum_data; } ;
typedef  TYPE_1__ SELF_TEST_POST_PARAMS ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ FIPS_STATE_ERROR ; 
 scalar_t__ FIPS_STATE_INIT ; 
 scalar_t__ FIPS_STATE_RUNNING ; 
 scalar_t__ FIPS_STATE_SELFTEST ; 
 scalar_t__ FIPS_state ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_hexstr2buf (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_integrity (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,long,int /*<<< orphan*/ ) ; 

int SELF_TEST_post(SELF_TEST_POST_PARAMS *st)
{
    int ok = 0;
    int kats_already_passed = 0;
    int on_demand_test = (FIPS_state != FIPS_STATE_INIT);
    long checksum_len;
    BIO *bio_module = NULL, *bio_indicator = NULL;
    unsigned char *module_checksum = NULL;
    unsigned char *indicator_checksum = NULL;

    if (st == NULL
            || FIPS_state == FIPS_STATE_ERROR
            || FIPS_state == FIPS_STATE_SELFTEST
            || st->module_checksum_data == NULL)
        goto end;

    module_checksum = OPENSSL_hexstr2buf(st->module_checksum_data,
                                         &checksum_len);
    if (module_checksum == NULL)
        goto end;
    bio_module = (*st->bio_new_file_cb)(st->module_filename, "rb");

    /* Always check the integrity of the fips module */
    if (bio_module == NULL
            || !verify_integrity(bio_module, st->bio_read_ex_cb,
                                 module_checksum, checksum_len, st->libctx))
        goto end;

    /* This will be NULL during installation - so the self test KATS will run */
    if (st->indicator_data != NULL) {
        /*
         * If the kats have already passed indicator is set - then check the
         * integrity of the indicator.
         */
        if (st->indicator_checksum_data == NULL)
            goto end;
        indicator_checksum = OPENSSL_hexstr2buf(st->indicator_checksum_data,
                                                &checksum_len);
        if (indicator_checksum == NULL)
            goto end;

        bio_indicator =
            (*st->bio_new_buffer_cb)(st->indicator_data,
                                     strlen(st->indicator_data));
        if (bio_indicator == NULL
                || !verify_integrity(bio_indicator, st->bio_read_ex_cb,
                                     indicator_checksum, checksum_len,
                                     st->libctx))
            goto end;
        else
            kats_already_passed = 1;
    }

    /* Only runs the KAT's during installation OR on_demand() */
    if (on_demand_test || kats_already_passed == 0) {
        /*TODO (3.0) Add self test KATS */
    }
    ok = 1;
end:
    OPENSSL_free(module_checksum);
    OPENSSL_free(indicator_checksum);

    if (st != NULL) {
        (*st->bio_free_cb)(bio_indicator);
        (*st->bio_free_cb)(bio_module);
    }
    FIPS_state = ok ? FIPS_STATE_RUNNING : FIPS_STATE_ERROR;

    return ok;
}