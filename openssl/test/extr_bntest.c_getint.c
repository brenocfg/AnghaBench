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
typedef  int /*<<< orphan*/  STANZA ;
typedef  scalar_t__ BN_ULONG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_get_word (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ulong_le (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getBN (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int getint(STANZA *s, int *out, const char *attribute)
{
    BIGNUM *ret;
    BN_ULONG word;
    int st = 0;

    if (!TEST_ptr(ret = getBN(s, attribute))
            || !TEST_ulong_le(word = BN_get_word(ret), INT_MAX))
        goto err;

    *out = (int)word;
    st = 1;
 err:
    BN_free(ret);
    return st;
}