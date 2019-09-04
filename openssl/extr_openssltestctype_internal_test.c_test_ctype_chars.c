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
 scalar_t__ TEST_int_eq (int,int) ; 
 scalar_t__ isalnum (int) ; 
 scalar_t__ isalpha (int) ; 
 scalar_t__ isascii (unsigned char) ; 
 scalar_t__ isblank (int) ; 
 scalar_t__ iscntrl (int) ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ isgraph (int) ; 
 scalar_t__ islower (int) ; 
 scalar_t__ isprint (int) ; 
 scalar_t__ ispunct (int) ; 
 scalar_t__ isspace (int) ; 
 scalar_t__ isupper (int) ; 
 scalar_t__ isxdigit (int) ; 
 scalar_t__ ossl_isalnum (int) ; 
 scalar_t__ ossl_isalpha (int) ; 
 scalar_t__ ossl_isascii (int) ; 
 scalar_t__ ossl_isblank (int) ; 
 scalar_t__ ossl_iscntrl (int) ; 
 scalar_t__ ossl_isdigit (int) ; 
 scalar_t__ ossl_isgraph (int) ; 
 scalar_t__ ossl_islower (int) ; 
 scalar_t__ ossl_isprint (int) ; 
 scalar_t__ ossl_ispunct (int) ; 
 scalar_t__ ossl_isspace (int) ; 
 scalar_t__ ossl_isupper (int) ; 
 scalar_t__ ossl_isxdigit (int) ; 

__attribute__((used)) static int test_ctype_chars(int n)
{
    if (!TEST_int_eq(isascii((unsigned char)n) != 0, ossl_isascii(n) != 0))
        return 0;

    if (!ossl_isascii(n))
        return 1;

    return TEST_int_eq(isalpha(n) != 0, ossl_isalpha(n) != 0)
           && TEST_int_eq(isalnum(n) != 0, ossl_isalnum(n) != 0)
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
           && TEST_int_eq(isblank(n) != 0, ossl_isblank(n) != 0)
#endif
           && TEST_int_eq(iscntrl(n) != 0, ossl_iscntrl(n) != 0)
           && TEST_int_eq(isdigit(n) != 0, ossl_isdigit(n) != 0)
           && TEST_int_eq(isgraph(n) != 0, ossl_isgraph(n) != 0)
           && TEST_int_eq(islower(n) != 0, ossl_islower(n) != 0)
           && TEST_int_eq(isprint(n) != 0, ossl_isprint(n) != 0)
           && TEST_int_eq(ispunct(n) != 0, ossl_ispunct(n) != 0)
           && TEST_int_eq(isspace(n) != 0, ossl_isspace(n) != 0)
           && TEST_int_eq(isupper(n) != 0, ossl_isupper(n) != 0)
           && TEST_int_eq(isxdigit(n) != 0, ossl_isxdigit(n) != 0);
}