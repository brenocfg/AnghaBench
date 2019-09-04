#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ numpairs; int errors; int /*<<< orphan*/  numtests; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ STANZA ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_eof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  file_test_run (TYPE_1__*) ; 
 int /*<<< orphan*/  test_clearstanza (TYPE_1__*) ; 
 int /*<<< orphan*/  test_end_file (TYPE_1__*) ; 
 char* test_get_argument (int) ; 
 scalar_t__ test_readstanza (TYPE_1__*) ; 
 int /*<<< orphan*/  test_start_file (TYPE_1__*,char*) ; 

__attribute__((used)) static int run_file_tests(int i)
{
    STANZA *s = NULL;
    char *testfile = test_get_argument(i);
    int c;

    if (!TEST_ptr(s = OPENSSL_zalloc(sizeof(*s))))
        return 0;
    if (!test_start_file(s, testfile)) {
        OPENSSL_free(s);
        return 0;
    }

    /* Read test file. */
    while (!BIO_eof(s->fp) && test_readstanza(s)) {
        if (s->numpairs == 0)
            continue;
        if (!file_test_run(s))
            s->errors++;
        s->numtests++;
        test_clearstanza(s);
    }
    test_end_file(s);
    c = s->errors;
    OPENSSL_free(s);

    return c == 0;
}