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
struct test_ctx {int dummy; } ;
struct mp_chmap_sel {int /*<<< orphan*/  member_0; } ;
struct mp_chmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAYOUTS (char*,...) ; 
 int /*<<< orphan*/  assert_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert_string_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  mp_chmap_diffn (struct mp_chmap*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_from_str (struct mp_chmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_chmap_sel_add_map (struct mp_chmap_sel*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_sel_fallback (struct mp_chmap_sel*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_set_unknown (struct mp_chmap*,int) ; 
 int /*<<< orphan*/  mp_chmap_to_str (struct mp_chmap*) ; 
 int /*<<< orphan*/  test_sel (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run(struct test_ctx *ctx)
{
    struct mp_chmap a;
    struct mp_chmap b;
    struct mp_chmap_sel s = {0};

    test_sel("5.1", "7.1", LAYOUTS("7.1"));
    test_sel("7.1", "5.1", LAYOUTS("5.1"));
    test_sel("7.1(wide-side)", "7.1", LAYOUTS("7.1"));
    test_sel("7.1(wide-side)", "5.1(side)", LAYOUTS("7.1", "5.1(side)"));
    test_sel("3.1", "5.1", LAYOUTS("7.1", "5.1", "2.1", "stereo", "mono"));
    test_sel("5.1", "7.1(rear)", LAYOUTS("7.1(rear)"));
    test_sel("5.1(side)", "5.1", LAYOUTS("5.1", "7.1"));
    test_sel("5.1", "7.1(alsa)", LAYOUTS("7.1(alsa)"));
    test_sel("mono", "stereo", LAYOUTS("stereo", "5.1"));
    test_sel("stereo", "stereo", LAYOUTS("stereo", "5.1"));
    test_sel("5.1(side)", "7.1(rear)", LAYOUTS("stereo", "7.1(rear)"));
    test_sel("7.1", "fl-fr-lfe-fc-bl-br-flc-frc",
             LAYOUTS("fl-fr-lfe-fc-bl-br-flc-frc", "3.0(back)"));

    mp_chmap_set_unknown(&a, 2);

    mp_chmap_from_str(&b, bstr0("5.1"));

    mp_chmap_sel_add_map(&s, &a);
    assert_false(mp_chmap_sel_fallback(&s, &b));
    assert_string_equal(mp_chmap_to_str(&b), "5.1");

    test_sel("quad", "quad(side)", LAYOUTS("quad(side)", "stereo"));
    test_sel("quad", "quad(side)", LAYOUTS("quad(side)", "7.0"));
    test_sel("quad", "quad(side)", LAYOUTS("7.0", "quad(side)"));
    test_sel("quad", "7.1(wide-side)", LAYOUTS("7.1(wide-side)", "stereo"));
    test_sel("quad", "7.1(wide-side)", LAYOUTS("stereo", "7.1(wide-side)"));
    test_sel("quad", "fl-fr-sl-sr",
             LAYOUTS("fl-fr-fc-bl-br", "fl-fr-sl-sr"));
    test_sel("quad", "fl-fr-bl-br-na-na-na-na",
             LAYOUTS("fl-fr-bl-br-na-na-na-na", "quad(side)", "stereo"));
    test_sel("quad", "fl-fr-bl-br-na-na-na-na",
             LAYOUTS("stereo", "quad(side)", "fl-fr-bl-br-na-na-na-na"));
    test_sel("fl-fr-fc-lfe-sl-sr", "fl-fr-lfe-fc-bl-br-na-na",
             LAYOUTS("fl-fr-lfe-fc-bl-br-na-na", "fl-fr-lfe-fc-bl-br-sdl-sdr"));
    test_sel("fl-fr-fc-lfe-sl-sr", "fl-fr-lfe-fc-bl-br-na-na",
             LAYOUTS("fl-fr-lfe-fc-bl-br-sdl-sdr", "fl-fr-lfe-fc-bl-br-na-na"));

    test_sel("na-fl-fr", "na-fl-fr", LAYOUTS("na-fl-fr-na", "fl-na-fr", "na-fl-fr",
                                             "fl-fr-na-na", "na-na-fl-fr"));

    mp_chmap_from_str(&a, bstr0("3.1"));
    mp_chmap_from_str(&b, bstr0("2.1"));

    assert_int_equal(mp_chmap_diffn(&a, &b), 1);

    mp_chmap_from_str(&b, bstr0("6.1(back)"));
    assert_int_equal(mp_chmap_diffn(&a, &b), 0);
    assert_int_equal(mp_chmap_diffn(&b, &a), 3);
}