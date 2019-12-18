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
 int /*<<< orphan*/  TEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_char_eq (char,char) ; 
 int /*<<< orphan*/  TEST_char_ge (char,char) ; 
 int /*<<< orphan*/  TEST_char_gt (char,char) ; 
 int /*<<< orphan*/  TEST_char_le (char,char) ; 
 int /*<<< orphan*/  TEST_char_lt (char,char) ; 
 int /*<<< orphan*/  TEST_char_ne (char,char) ; 

__attribute__((used)) static int test_char(void)
{
    if (!TEST(1, TEST_char_eq('a', 'a'))
        | !TEST(0, TEST_char_eq('a', 'A'))
        | !TEST(1, TEST_char_ne('a', 'c'))
        | !TEST(0, TEST_char_ne('e', 'e'))
        | !TEST(1, TEST_char_lt('i', 'x'))
        | !TEST(0, TEST_char_lt('x', 'i'))
        | !TEST(1, TEST_char_le('i', 'x'))
        | !TEST(1, TEST_char_le('n', 'n'))
        | !TEST(0, TEST_char_le('x', 'i'))
        | !TEST(1, TEST_char_gt('w', 'n'))
        | !TEST(0, TEST_char_gt('n', 'w'))
        | !TEST(1, TEST_char_ge('w', 'n'))
        | !TEST(1, TEST_char_ge('p', 'p'))
        | !TEST(0, TEST_char_ge('n', 'w')))
        goto err;
    return 1;

err:
    return 0;
}