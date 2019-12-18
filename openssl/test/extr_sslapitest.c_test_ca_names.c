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

/* Variables and functions */
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int test_ca_names_int (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_ca_names(int tst)
{
    int testresult = 1;

#ifndef OPENSSL_NO_TLS1_2
    testresult &= test_ca_names_int(TLS1_2_VERSION, tst);
#endif
#ifndef OPENSSL_NO_TLS1_3
    testresult &= test_ca_names_int(TLS1_3_VERSION, tst);
#endif

    return testresult;
}