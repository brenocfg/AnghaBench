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
struct TYPE_2__ {int /*<<< orphan*/  digest; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  HMAC (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  TEST_str_eq (char*,int /*<<< orphan*/ ) ; 
 char* pt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* test ; 

__attribute__((used)) static int test_hmac_single_shot(void)
{
    char *p;

    /* Test single-shot with an empty key. */
    p = pt(HMAC(EVP_sha1(), NULL, 0, test[4].data, test[4].data_len,
                NULL, NULL), SHA_DIGEST_LENGTH);
    if (!TEST_str_eq(p, test[4].digest))
        return 0;

    return 1;
}