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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lcg_calculate_constants (int,int*,int*,int /*<<< orphan*/ ) ; 
 int lcg_verify (int,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

int
lcg_selftest(void)
{
    unsigned i;
    int is_success = 0;
    uint64_t m, a, c;


    m = 3015 * 3;

    for (i=0; i<5; i++) {
        a = 0;
        c = 0;

        m += 10 + i;

        lcg_calculate_constants(m, &a, &c, 0);

        is_success = lcg_verify(a, c, m, m);

        if (!is_success) {
            fprintf(stderr, "LCG: randomization failed\n");
            return 1; /*fail*/
        }
    }

    return 0; /*success*/
}