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
 int /*<<< orphan*/  assert_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  searchandreplace (char*,char*,char*) ; 

__attribute__((used)) static void
pass_any_null_param__returns_null() {

    char DUMMY[] = "DUMMY";

    assert_null(searchandreplace(NULL,DUMMY,DUMMY));
    assert_null(searchandreplace(DUMMY,NULL,DUMMY));
    assert_null(searchandreplace(DUMMY,DUMMY,NULL));
}