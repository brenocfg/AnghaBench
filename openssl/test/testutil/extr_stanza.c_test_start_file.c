#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* test_file; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ STANZA ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  TEST_info (char*,char const*) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_test_title (char const*) ; 

int test_start_file(STANZA *s, const char *testfile)
{
    TEST_info("Reading %s", testfile);
    set_test_title(testfile);
    memset(s, 0, sizeof(*s));
    if (!TEST_ptr(s->fp = BIO_new_file(testfile, "r")))
        return 0;
    s->test_file = testfile;
    return 1;
}