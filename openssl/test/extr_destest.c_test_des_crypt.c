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
 int /*<<< orphan*/  DES_crypt (char*,char*) ; 
 int /*<<< orphan*/  TEST_ptr_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_str_eq (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_des_crypt(void)
{
    if (!TEST_str_eq("efGnQx2725bI2", DES_crypt("testing", "ef")))
        return 0;
    if (!TEST_str_eq("yA1Rp/1hZXIJk", DES_crypt("bca76;23", "yA")))
        return 0;

    if (!TEST_ptr_null(DES_crypt("testing", "y\202")))
        return 0;
    if (!TEST_ptr_null(DES_crypt("testing", "\0A")))
        return 0;
    if (!TEST_ptr_null(DES_crypt("testing", "A")))
        return 0;
    return 1;
}