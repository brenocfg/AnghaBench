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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  k ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_info (char*,unsigned int) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X448 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * in_scalar1 ; 
 int /*<<< orphan*/ * in_scalar2 ; 
 int /*<<< orphan*/ * in_u1 ; 
 int /*<<< orphan*/ * in_u2 ; 
 int /*<<< orphan*/ * in_u3 ; 
 unsigned int max ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_u1 ; 
 int /*<<< orphan*/  out_u2 ; 
 int /*<<< orphan*/ * out_u3 ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int test_x448(void)
{
    uint8_t u[56], k[56], out[56];
    unsigned int i;
    int j = -1;

    /* Curve448 tests */

    if (!TEST_true(X448(out, in_scalar1, in_u1))
          || !TEST_int_eq(memcmp(out, out_u1, sizeof(out)), 0)
          || !TEST_true(X448(out, in_scalar2, in_u2))
          || !TEST_int_eq(memcmp(out, out_u2, sizeof(out)), 0))
        return 0;

    memcpy(u, in_u3, sizeof(u));
    memcpy(k, in_u3, sizeof(k));
    for (i = 1; i <= max; i++) {
        if (verbose && i % 10000 == 0) {
            printf(".");
            fflush(stdout);
        }

        if (!TEST_true(X448(out, k, u)))
            return 0;

        if (i == 1 || i == 1000 || i == 1000000) {
            j++;
            if (!TEST_int_eq(memcmp(out, out_u3[j], sizeof(out)), 0)) {
                TEST_info("Failed at iteration %d", i);
                return 0;
            }
        }
        memcpy(u, k, sizeof(u));
        memcpy(k, out, sizeof(k));
    }

    return 1;
}