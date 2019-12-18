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
 int /*<<< orphan*/  assert_non_null (char*) ; 
 int /*<<< orphan*/  assert_string_equal (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* searchandreplace (char*,char*,char*) ; 

__attribute__((used)) static void
replace_single_char__one_time__match_is_replaced() {
    char *replaced = searchandreplace("X","X","Y");

    assert_non_null(replaced);
    assert_string_equal("Y", replaced);

    free(replaced);
}