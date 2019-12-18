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
 int /*<<< orphan*/  DSA_generate_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsakey ; 
 int /*<<< orphan*/  load_dsa_params () ; 

__attribute__((used)) static int genkeys(void)
{
    if (!TEST_ptr(dsakey = load_dsa_params()))
        return 0;

    if (!TEST_int_eq(DSA_generate_key(dsakey), 1))
        return 0;

    return 1;
}