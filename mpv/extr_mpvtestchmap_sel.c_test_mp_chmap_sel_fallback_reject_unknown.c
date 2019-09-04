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
struct mp_chmap_sel {int /*<<< orphan*/  member_0; } ;
struct mp_chmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_string_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  mp_chmap_from_str (struct mp_chmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_chmap_sel_add_map (struct mp_chmap_sel*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_sel_fallback (struct mp_chmap_sel*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_set_unknown (struct mp_chmap*,int) ; 
 int /*<<< orphan*/  mp_chmap_to_str (struct mp_chmap*) ; 

__attribute__((used)) static void test_mp_chmap_sel_fallback_reject_unknown(void **state) {
    struct mp_chmap a;
    struct mp_chmap b;
    struct mp_chmap_sel s = {0};

    mp_chmap_set_unknown(&a, 2);

    mp_chmap_from_str(&b, bstr0("5.1"));

    mp_chmap_sel_add_map(&s, &a);
    assert_false(mp_chmap_sel_fallback(&s, &b));
    assert_string_equal(mp_chmap_to_str(&b), "5.1");
}