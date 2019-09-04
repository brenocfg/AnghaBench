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
struct CMUnitTest {int dummy; } ;

/* Variables and functions */
 int cmocka_run_group_tests (struct CMUnitTest const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct CMUnitTest const cmocka_unit_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_downmix ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_incompatible ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_inexact_equivalent ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_minimal_downmix ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_mono_to_stereo ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_more_replacements ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_na_channels ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_no_downmix ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_prefer_closest_upmix ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_prefer_compatible ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_reject_unknown ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_stereo_to_stereo ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_upmix ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_use_replacements ; 
 int /*<<< orphan*/  test_mp_chmap_sel_fallback_works_on_alsa_chmaps ; 

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_mp_chmap_sel_fallback_upmix),
        cmocka_unit_test(test_mp_chmap_sel_fallback_downmix),
        cmocka_unit_test(test_mp_chmap_sel_fallback_incompatible),
        cmocka_unit_test(test_mp_chmap_sel_fallback_prefer_compatible),
        cmocka_unit_test(test_mp_chmap_sel_fallback_prefer_closest_upmix),
        cmocka_unit_test(test_mp_chmap_sel_fallback_use_replacements),
        cmocka_unit_test(test_mp_chmap_sel_fallback_inexact_equivalent),
        cmocka_unit_test(test_mp_chmap_sel_fallback_works_on_alsa_chmaps),
        cmocka_unit_test(test_mp_chmap_sel_fallback_mono_to_stereo),
        cmocka_unit_test(test_mp_chmap_sel_fallback_stereo_to_stereo),
        cmocka_unit_test(test_mp_chmap_sel_fallback_no_downmix),
        cmocka_unit_test(test_mp_chmap_sel_fallback_minimal_downmix),
        cmocka_unit_test(test_mp_chmap_sel_fallback_reject_unknown),
        cmocka_unit_test(test_mp_chmap_sel_fallback_more_replacements),
        cmocka_unit_test(test_mp_chmap_sel_fallback_na_channels),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}