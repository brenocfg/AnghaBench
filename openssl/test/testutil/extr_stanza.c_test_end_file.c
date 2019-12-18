#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fp; int /*<<< orphan*/  numskip; int /*<<< orphan*/  errors; int /*<<< orphan*/  numtests; } ;
typedef  TYPE_1__ STANZA ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int test_end_file(STANZA *s)
{
    TEST_info("Completed %d tests with %d errors and %d skipped",
              s->numtests, s->errors, s->numskip);
    BIO_free(s->fp);
    return 1;
}