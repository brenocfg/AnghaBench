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
struct set_name_fn {int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ *,char const* const) ;int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_cert () ; 
 struct set_name_fn* name_fns ; 
 char** names ; 
 int /*<<< orphan*/  run_cert (int /*<<< orphan*/ *,char const* const,struct set_name_fn const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char const* const) ; 

__attribute__((used)) static int call_run_cert(int i)
{
    int failed = 0;
    const struct set_name_fn *pfn = &name_fns[i];
    X509 *crt;
    const char *const *pname;

    TEST_info("%s", pfn->name);
    for (pname = names; *pname != NULL; pname++) {
        if (!TEST_ptr(crt = make_cert())
             || !TEST_true(pfn->fn(crt, *pname))
             || !run_cert(crt, *pname, pfn))
            failed = 1;
        X509_free(crt);
    }
    return failed == 0;
}