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
 int /*<<< orphan*/  LAYOUTS (char*,char*) ; 
 int /*<<< orphan*/  test_sel (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_mp_chmap_sel_fallback_stereo_to_stereo(void **state) {
    test_sel("stereo", "stereo", LAYOUTS("stereo", "5.1"));
}