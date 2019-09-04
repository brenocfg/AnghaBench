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
 int NID_undef ; 
 char* OBJ_nid2ln (int) ; 
 int /*<<< orphan*/  TEST_error (char*,char const*,char*,char*) ; 

__attribute__((used)) static int check_nid(const char *name, int expected_nid, int nid)
{
    if (expected_nid == 0 || expected_nid == nid)
        return 1;
    TEST_error("%s type mismatch, %s vs %s\n",
               name, OBJ_nid2ln(expected_nid),
               nid == NID_undef ? "absent" : OBJ_nid2ln(nid));
    return 0;
}