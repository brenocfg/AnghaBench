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
struct TYPE_10__ {scalar_t__ numpairs; int /*<<< orphan*/  curr; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ STANZA ;
typedef  int /*<<< orphan*/  PARAM_CONVERSION ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_eof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  param_conversion_load_stanza (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  param_conversion_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_clearstanza (TYPE_1__*) ; 
 int /*<<< orphan*/  test_end_file (TYPE_1__*) ; 
 char* test_get_argument (int) ; 
 int /*<<< orphan*/  test_readstanza (TYPE_1__*) ; 
 int /*<<< orphan*/  test_start_file (TYPE_1__*,char const*) ; 

__attribute__((used)) static int run_param_file_tests(int i)
{
    STANZA *s;
    PARAM_CONVERSION pc;
    const char *testfile = test_get_argument(i);
    int res = 1;

    if (!TEST_ptr(s = OPENSSL_zalloc(sizeof(*s))))
        return 0;
    if (!test_start_file(s, testfile)) {
        OPENSSL_free(s);
        return 0;
    }

    while (!BIO_eof(s->fp)) {
        if (!test_readstanza(s)) {
            res = 0;
            goto end;
        }
        if (s->numpairs != 0)
            if (!param_conversion_load_stanza(&pc, s)
                || !param_conversion_test(&pc, s->curr))
                res = 0;
        test_clearstanza(s);
    }
end:
    test_end_file(s);
    OPENSSL_free(s);
    return res;
}