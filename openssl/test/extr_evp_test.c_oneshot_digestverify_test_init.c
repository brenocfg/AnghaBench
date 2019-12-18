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
typedef  int /*<<< orphan*/  EVP_TEST ;

/* Variables and functions */
 int digestsigver_test_init (int /*<<< orphan*/ *,char const*,int,int) ; 

__attribute__((used)) static int oneshot_digestverify_test_init(EVP_TEST *t, const char *alg)
{
    return digestsigver_test_init(t, alg, 1, 1);
}