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
 scalar_t__ TEST_char_eq (char,char) ; 
 scalar_t__ TEST_char_le (char,char) ; 
 scalar_t__ TEST_char_lt (int /*<<< orphan*/ ,char) ; 
 scalar_t__ TEST_char_ne (char,char) ; 
 scalar_t__ TEST_int_eq (int,int) ; 
 scalar_t__ TEST_int_gt (int,int) ; 
 scalar_t__ TEST_int_le (int,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_int_ne (int,int) ; 
 scalar_t__ TEST_long_eq (long,long) ; 
 scalar_t__ TEST_long_lt (long,long) ; 
 scalar_t__ TEST_long_ne (long,long) ; 
 scalar_t__ TEST_mem_eq (char*,int,char*,int) ; 
 scalar_t__ TEST_mem_ne (int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ TEST_ptr (char*) ; 
 scalar_t__ TEST_ptr_eq (char*,char*) ; 
 scalar_t__ TEST_ptr_null (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_size_t_eq (size_t,int) ; 
 scalar_t__ TEST_str_eq (char*,char*) ; 
 scalar_t__ TEST_str_ne (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TEST_uchar_eq (unsigned char,int) ; 
 scalar_t__ TEST_ulong_eq (unsigned long,int) ; 

__attribute__((used)) static int test_single_eval(void)
{
    int i = 4;
    long l = -9000;
    char c = 'd';
    unsigned char uc = 22;
    unsigned long ul = 500;
    size_t st = 1234;
    char buf[4] = { 0 }, *p = buf;

           /* int */
    return TEST_int_eq(i++, 4)
           && TEST_int_eq(i, 5)
           && TEST_int_gt(++i, 5)
           && TEST_int_le(5, i++)
           && TEST_int_ne(--i, 5)
           && TEST_int_eq(12, i *= 2)
           /* Long */
           && TEST_long_eq(l--, -9000L)
           && TEST_long_eq(++l, -9000L)
           && TEST_long_ne(-9000L, l /= 2)
           && TEST_long_lt(--l, -4500L)
           /* char */
           && TEST_char_eq(++c, 'e')
           && TEST_char_eq('e', c--)
           && TEST_char_ne('d', --c)
           && TEST_char_le('b', --c)
           && TEST_char_lt(c++, 'c')
           /* unsigned char */
           && TEST_uchar_eq(22, uc++)
           && TEST_uchar_eq(uc /= 2, 11)
           && TEST_ulong_eq(ul ^= 1, 501)
           && TEST_ulong_eq(502, ul ^= 3)
           && TEST_ulong_eq(ul = ul * 3 - 6, 1500)
           /* size_t */
           && TEST_size_t_eq((--i, st++), 1234)
           && TEST_size_t_eq(st, 1235)
           && TEST_int_eq(11, i)
           /* pointers */
           && TEST_ptr_eq(p++, buf)
           && TEST_ptr_eq(buf + 2, ++p)
           && TEST_ptr_eq(buf, p -= 2)
           && TEST_ptr(++p)
           && TEST_ptr_eq(p, buf + 1)
           && TEST_ptr_null(p = NULL)
           /* strings */
           && TEST_str_eq(p = &("123456"[1]), "23456")
           && TEST_str_eq("3456", ++p)
           && TEST_str_ne(p++, "456")
           /* memory */
           && TEST_mem_eq(--p, sizeof("3456"), "3456", sizeof("3456"))
           && TEST_mem_ne(p++, sizeof("456"), "456", sizeof("456"))
           && TEST_mem_eq(p--, sizeof("456"), "456", sizeof("456"));
}