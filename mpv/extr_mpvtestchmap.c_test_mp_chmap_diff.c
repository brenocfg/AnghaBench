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
struct mp_chmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  mp_chmap_diffn (struct mp_chmap*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_from_str (struct mp_chmap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_mp_chmap_diff(void **state) {
    struct mp_chmap a;
    struct mp_chmap b;

    mp_chmap_from_str(&a, bstr0("3.1"));
    mp_chmap_from_str(&b, bstr0("2.1"));

    assert_int_equal(mp_chmap_diffn(&a, &b), 1);

    mp_chmap_from_str(&b, bstr0("6.1(back)"));
    assert_int_equal(mp_chmap_diffn(&a, &b), 0);
    assert_int_equal(mp_chmap_diffn(&b, &a), 3);
}