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
struct TYPE_3__ {int /*<<< orphan*/  expected; scalar_t__ input; } ;
typedef  TYPE_1__ TESTDATA ;
typedef  int /*<<< orphan*/  MDC2_CTX ;

/* Variables and functions */
 int MDC2_DIGEST_LENGTH ; 
 int /*<<< orphan*/  MDC2_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDC2_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDC2_Update (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_info (char*,int) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,int,unsigned char*,int) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 TYPE_1__* tests ; 

__attribute__((used)) static int test_mdc2(int idx)
{
    unsigned char md[MDC2_DIGEST_LENGTH];
    MDC2_CTX c;
    const TESTDATA testdata = tests[idx];

    MDC2_Init(&c);
    MDC2_Update(&c, (const unsigned char *)testdata.input,
                strlen(testdata.input));
    MDC2_Final(&(md[0]), &c);

    if (!TEST_mem_eq(testdata.expected, MDC2_DIGEST_LENGTH,
                     md, MDC2_DIGEST_LENGTH)) {
        TEST_info("mdc2 test %d: unexpected output", idx);
        return 0;
    }

    return 1;
}