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
 int /*<<< orphan*/  LAYOUTS (char*,char*,...) ; 
 int /*<<< orphan*/  test_sel (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_mp_chmap_sel_fallback_more_replacements(void **state) {
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
}