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
struct SN_env {int ket; int c; int lb; int* p; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_9 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r_exception2(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 158 */
    if (z->c - 5 <= z->lb || (z->p[z->c - 1] != 100 && z->p[z->c - 1] != 103)) return 0; /* substring, line 158 */
    if (!(find_among_b(z, a_9, 8))) return 0;
    z->bra = z->c; /* ], line 158 */
    if (z->c > z->lb) return 0; /* atlimit, line 158 */
    return 1;
}