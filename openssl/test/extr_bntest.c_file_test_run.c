#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* member_0; int /*<<< orphan*/  name; int /*<<< orphan*/  (* func ) (TYPE_1__*) ;int /*<<< orphan*/  member_1; } ;
struct TYPE_7__ {int /*<<< orphan*/  start; int /*<<< orphan*/  test_file; } ;
typedef  TYPE_1__ STANZA ;
typedef  TYPE_2__ FILETEST ;

/* Variables and functions */
 int OSSL_NELEM (TYPE_2__ const*) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
#define  file_exp 139 
#define  file_gcd 138 
#define  file_lshift 137 
#define  file_lshift1 136 
#define  file_modexp 135 
#define  file_modmul 134 
#define  file_modsqrt 133 
#define  file_product 132 
#define  file_quotient 131 
#define  file_rshift 130 
#define  file_square 129 
#define  file_sum 128 
 int /*<<< orphan*/ * findattr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int file_test_run(STANZA *s)
{
    static const FILETEST filetests[] = {
        {"Sum", file_sum},
        {"LShift1", file_lshift1},
        {"LShift", file_lshift},
        {"RShift", file_rshift},
        {"Square", file_square},
        {"Product", file_product},
        {"Quotient", file_quotient},
        {"ModMul", file_modmul},
        {"ModExp", file_modexp},
        {"Exp", file_exp},
        {"ModSqrt", file_modsqrt},
        {"GCD", file_gcd},
    };
    int numtests = OSSL_NELEM(filetests);
    const FILETEST *tp = filetests;

    for ( ; --numtests >= 0; tp++) {
        if (findattr(s, tp->name) != NULL) {
            if (!tp->func(s)) {
                TEST_info("%s:%d: Failed %s test",
                          s->test_file, s->start, tp->name);
                return 0;
            }
            return 1;
        }
    }
    TEST_info("%s:%d: Unknown test", s->test_file, s->start);
    return 0;
}