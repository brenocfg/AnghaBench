#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  out ;
struct TYPE_8__ {unsigned char* data; size_t size; } ;
struct TYPE_7__ {unsigned char* data; } ;
struct TYPE_6__ {unsigned char* data; size_t size; } ;
struct TYPE_9__ {TYPE_3__ expected; TYPE_2__ key; TYPE_1__ input; } ;
typedef  TYPE_4__ TESTDATA ;
typedef  int /*<<< orphan*/  POLY1305 ;

/* Variables and functions */
 int /*<<< orphan*/  Poly1305_Final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  Poly1305_Init (int /*<<< orphan*/ *,unsigned char const*) ; 
 int /*<<< orphan*/  Poly1305_Update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  TEST_info (char*,int,...) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,size_t,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int) ; 
 TYPE_4__* tests ; 

__attribute__((used)) static int test_poly1305(int idx)
{
    POLY1305 poly1305;
    const TESTDATA test = tests[idx];
    const unsigned char *in = test.input.data;
    size_t inlen = test.input.size;
    const unsigned char *key = test.key.data;
    const unsigned char *expected = test.expected.data;
    size_t expectedlen = test.expected.size;
    unsigned char out[16];

    if (!TEST_size_t_eq(expectedlen, sizeof(out)))
        return 0;

    Poly1305_Init(&poly1305, key);
    Poly1305_Update(&poly1305, in, inlen);
    Poly1305_Final(&poly1305, out);

    if (!TEST_mem_eq(out, expectedlen, expected, expectedlen)) {
        TEST_info("Poly1305 test #%d failed.", idx);
        return 0;
    }

    if (inlen > 16) {
        Poly1305_Init(&poly1305, key);
        Poly1305_Update(&poly1305, in, 1);
        Poly1305_Update(&poly1305, in+1, inlen-1);
        Poly1305_Final(&poly1305, out);

        if (!TEST_mem_eq(out, expectedlen, expected, expectedlen)) {
            TEST_info("Poly1305 test #%d/1+(N-1) failed.", idx);
            return 0;
        }
    }

    if (inlen > 32) {
        size_t half = inlen / 2;

        Poly1305_Init(&poly1305, key);
        Poly1305_Update(&poly1305, in, half);
        Poly1305_Update(&poly1305, in+half, inlen-half);
        Poly1305_Final(&poly1305, out);

        if (!TEST_mem_eq(out, expectedlen, expected, expectedlen)) {
            TEST_info("Poly1305 test #%d/2 failed.", idx);
            return 0;
        }

        for (half = 16; half < inlen; half += 16) {
            Poly1305_Init(&poly1305, key);
            Poly1305_Update(&poly1305, in, half);
            Poly1305_Update(&poly1305, in+half, inlen-half);
            Poly1305_Final(&poly1305, out);

            if (!TEST_mem_eq(out, expectedlen, expected, expectedlen)) {
                TEST_info("Poly1305 test #%d/%zu+%zu failed.",
                          idx, half, inlen-half);
                return 0;
            }
        }
    }

    return 1;
}