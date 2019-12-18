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
typedef  int /*<<< orphan*/  OSSL_NAMEMAP ;

/* Variables and functions */
 char* ALIAS1 ; 
 char* ALIAS1_UC ; 
 char* NAME1 ; 
 char* NAME2 ; 
 scalar_t__ TEST_int_eq (int,int) ; 
 scalar_t__ TEST_int_ne (int,int /*<<< orphan*/ ) ; 
 int ossl_namemap_add (int /*<<< orphan*/ *,int,char*) ; 
 int ossl_namemap_name2num (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int test_namemap(OSSL_NAMEMAP *nm)
{
    int num1 = ossl_namemap_add(nm, 0, NAME1);
    int num2 = ossl_namemap_add(nm, 0, NAME2);
    int num3 = ossl_namemap_add(nm, num1, ALIAS1);
    int num4 = ossl_namemap_add(nm, 0, ALIAS1_UC);
    int check1 = ossl_namemap_name2num(nm, NAME1);
    int check2 = ossl_namemap_name2num(nm, NAME2);
    int check3 = ossl_namemap_name2num(nm, ALIAS1);
    int check4 = ossl_namemap_name2num(nm, ALIAS1_UC);
    int false1 = ossl_namemap_name2num(nm, "foo");

    return TEST_int_ne(num1, 0)
        && TEST_int_ne(num2, 0)
        && TEST_int_eq(num1, num3)
        && TEST_int_eq(num3, num4)
        && TEST_int_eq(num1, check1)
        && TEST_int_eq(num2, check2)
        && TEST_int_eq(num3, check3)
        && TEST_int_eq(num4, check4)
        && TEST_int_eq(false1, 0);
}