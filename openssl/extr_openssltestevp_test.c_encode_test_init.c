#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  encoding; } ;
struct TYPE_8__ {TYPE_2__* data; TYPE_2__* expected_err; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  TYPE_2__ ENCODE_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  BASE64_CANONICAL_ENCODING ; 
 int /*<<< orphan*/  BASE64_INVALID_ENCODING ; 
 int /*<<< orphan*/  BASE64_VALID_ENCODING ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 TYPE_2__* OPENSSL_strdup (char*) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_error (char*,char const*) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_2__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int encode_test_init(EVP_TEST *t, const char *encoding)
{
    ENCODE_DATA *edata;

    if (!TEST_ptr(edata = OPENSSL_zalloc(sizeof(*edata))))
        return 0;
    if (strcmp(encoding, "canonical") == 0) {
        edata->encoding = BASE64_CANONICAL_ENCODING;
    } else if (strcmp(encoding, "valid") == 0) {
        edata->encoding = BASE64_VALID_ENCODING;
    } else if (strcmp(encoding, "invalid") == 0) {
        edata->encoding = BASE64_INVALID_ENCODING;
        if (!TEST_ptr(t->expected_err = OPENSSL_strdup("DECODE_ERROR")))
            goto err;
    } else {
        TEST_error("Bad encoding: %s."
                   " Should be one of {canonical, valid, invalid}",
                   encoding);
        goto err;
    }
    t->data = edata;
    return 1;
err:
    OPENSSL_free(edata);
    return 0;
}