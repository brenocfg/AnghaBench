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
typedef  int /*<<< orphan*/  check ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_false (int) ; 
 int /*<<< orphan*/  TEST_int_eq (size_t,int) ; 
 int /*<<< orphan*/  TEST_int_ge (int,int) ; 
 int /*<<< orphan*/  TEST_int_le (int,int) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned char,int) ; 

__attribute__((used)) static int sanity_check_bytes(size_t (*rng)(unsigned char *, size_t),
    int rounds, int min_failures, int max_retries, int max_zero_words)
{
    int testresult = 0;
    unsigned char prior[31] = {0}, buf[31] = {0}, check[7];
    int failures = 0, zero_words = 0;

    int i;
    for (i = 0; i < rounds; i++) {
        size_t generated = 0;

        int retry;
        for (retry = 0; retry < max_retries; retry++) {
            generated = rng(buf, sizeof(buf));
            if (generated == sizeof(buf))
                break;
            failures++;
        }

        /*-
         * Verify that we don't have too many unexpected runs of zeroes,
         * implying that we might be accidentally using the 32-bit RDRAND
         * instead of the 64-bit one on 64-bit systems.
         */
        size_t j;
        for (j = 0; j < sizeof(buf) - 1; j++) {
            if (buf[j] == 0 && buf[j+1] == 0) {
                zero_words++;
            }
        }

        if (!TEST_int_eq(generated, sizeof(buf)))
            goto end;
        if (!TEST_false(!memcmp(prior, buf, sizeof(buf))))
            goto end;

        /* Verify that the last 7 bytes of buf aren't all the same value */
        unsigned char *tail = &buf[sizeof(buf) - sizeof(check)];
        memset(check, tail[0], 7);
        if (!TEST_false(!memcmp(check, tail, sizeof(check))))
            goto end;

        /* Save the result and make sure it's different next time */
        memcpy(prior, buf, sizeof(buf));
    }

    if (!TEST_int_le(zero_words, max_zero_words))
        goto end;

    if (!TEST_int_ge(failures, min_failures))
        goto end;

    testresult = 1;
end:
    return testresult;
}