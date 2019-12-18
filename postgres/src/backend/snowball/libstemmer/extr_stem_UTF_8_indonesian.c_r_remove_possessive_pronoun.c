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
struct SN_env {int ket; int c; int lb; int* p; int bra; int* I; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_1 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_remove_possessive_pronoun(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 57 */
    if (z->c - 1 <= z->lb || (z->p[z->c - 1] != 97 && z->p[z->c - 1] != 117)) return 0; /* substring, line 57 */
    if (!(find_among_b(z, a_1, 3))) return 0;
    z->bra = z->c; /* ], line 57 */
    {   int ret = slice_del(z); /* delete, line 58 */
        if (ret < 0) return ret;
    }
    z->I[0] -= 1; /* $measure -= <integer expression>, line 58 */
    return 1;
}