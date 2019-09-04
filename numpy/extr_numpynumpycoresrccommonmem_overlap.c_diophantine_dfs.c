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
typedef  int npy_int64 ;
typedef  int /*<<< orphan*/  npy_extint128_t ;
typedef  scalar_t__ mem_overlap_t ;
struct TYPE_4__ {int a; int ub; } ;
typedef  TYPE_1__ diophantine_term_t ;
typedef  int /*<<< orphan*/  Py_ssize_t ;

/* Variables and functions */
 scalar_t__ MEM_OVERLAP_NO ; 
 scalar_t__ MEM_OVERLAP_OVERFLOW ; 
 scalar_t__ MEM_OVERLAP_TOO_HARD ; 
 scalar_t__ MEM_OVERLAP_YES ; 
 int /*<<< orphan*/  add_128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ceildiv_128_64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  floordiv_128_64 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gt_128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_64_64 (int,int) ; 
 int /*<<< orphan*/  neg_128 (int /*<<< orphan*/ ) ; 
 int safe_mul (int,int,char*) ; 
 int safe_sub (int,int,char*) ; 
 int /*<<< orphan*/  sub_128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  to_128 (int) ; 
 int to_64 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static mem_overlap_t
diophantine_dfs(unsigned int n,
                unsigned int v,
                diophantine_term_t *E,
                diophantine_term_t *Ep,
                npy_int64 *Gamma, npy_int64 *Epsilon,
                npy_int64 b,
                Py_ssize_t max_work,
                int require_ub_nontrivial,
                npy_int64 *x,
                Py_ssize_t *count)
{
    npy_int64 a_gcd, gamma, epsilon, a1, u1, a2, u2, c, r, c1, c2, t, t_l, t_u, b2, x1, x2;
    npy_extint128_t x10, x20, t_l1, t_l2, t_u1, t_u2;
    mem_overlap_t res;
    char overflow = 0;

    if (max_work >= 0 && *count >= max_work) {
        return MEM_OVERLAP_TOO_HARD;
    }

    /* Fetch precomputed values for the reduced problem */
    if (v == 1) {
        a1 = E[0].a;
        u1 = E[0].ub;
    }
    else {
        a1 = Ep[v-2].a;
        u1 = Ep[v-2].ub;
    }

    a2 = E[v].a;
    u2 = E[v].ub;

    a_gcd = Ep[v-1].a;
    gamma = Gamma[v-1];
    epsilon = Epsilon[v-1];

    /* Generate set of allowed solutions */
    c = b / a_gcd;
    r = b % a_gcd;
    if (r != 0) {
        ++*count;
        return MEM_OVERLAP_NO;
    }

    c1 = a2 / a_gcd;
    c2 = a1 / a_gcd;

    /*
      The set to enumerate is:
      x1 = gamma*c + c1*t
      x2 = epsilon*c - c2*t
      t integer
      0 <= x1 <= u1
      0 <= x2 <= u2
      and we have c, c1, c2 >= 0
     */

    x10 = mul_64_64(gamma, c);
    x20 = mul_64_64(epsilon, c);

    t_l1 = ceildiv_128_64(neg_128(x10), c1);
    t_l2 = ceildiv_128_64(sub_128(x20, to_128(u2), &overflow), c2);

    t_u1 = floordiv_128_64(sub_128(to_128(u1), x10, &overflow), c1);
    t_u2 = floordiv_128_64(x20, c2);

    if (overflow) {
        return MEM_OVERLAP_OVERFLOW;
    }

    if (gt_128(t_l2, t_l1)) {
        t_l1 = t_l2;
    }

    if (gt_128(t_u1, t_u2)) {
        t_u1 = t_u2;
    }

    if (gt_128(t_l1, t_u1)) {
        ++*count;
        return MEM_OVERLAP_NO;
    }

    t_l = to_64(t_l1, &overflow);
    t_u = to_64(t_u1, &overflow);

    x10 = add_128(x10, mul_64_64(c1, t_l), &overflow);
    x20 = sub_128(x20, mul_64_64(c2, t_l), &overflow);

    t_u = safe_sub(t_u, t_l, &overflow);
    t_l = 0;
    x1 = to_64(x10, &overflow);
    x2 = to_64(x20, &overflow);

    if (overflow) {
        return MEM_OVERLAP_OVERFLOW;
    }

    /* The bounds t_l, t_u ensure the x computed below do not overflow */

    if (v == 1) {
        /* Base case */
        if (t_u >= t_l) {
            x[0] = x1 + c1*t_l;
            x[1] = x2 - c2*t_l;
            if (require_ub_nontrivial) {
                unsigned int j;
                int is_ub_trivial;

                is_ub_trivial = 1;
                for (j = 0; j < n; ++j) {
                    if (x[j] != E[j].ub/2) {
                        is_ub_trivial = 0;
                        break;
                    }
                }

                if (is_ub_trivial) {
                    /* Ignore 'trivial' solution */
                    ++*count;
                    return MEM_OVERLAP_NO;
                }
            }
            return MEM_OVERLAP_YES;
        }
        ++*count;
        return MEM_OVERLAP_NO;
    }
    else {
        /* Recurse to all candidates */
        for (t = t_l; t <= t_u; ++t) {
            x[v] = x2 - c2*t;

            /* b2 = b - a2*x[v]; */
            b2 = safe_sub(b, safe_mul(a2, x[v], &overflow), &overflow);
            if (overflow) {
                return MEM_OVERLAP_OVERFLOW;
            }

            res = diophantine_dfs(n, v-1, E, Ep, Gamma, Epsilon,
                                  b2, max_work, require_ub_nontrivial,
                                  x, count);
            if (res != MEM_OVERLAP_NO) {
                return res;
            }
        }
        ++*count;
        return MEM_OVERLAP_NO;
    }
}