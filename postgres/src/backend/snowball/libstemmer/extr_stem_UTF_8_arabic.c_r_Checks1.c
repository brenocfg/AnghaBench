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
struct SN_env {int bra; int c; int l; int* p; int ket; int* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_3 ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int len_utf8 (int*) ; 

__attribute__((used)) static int r_Checks1(struct SN_env * z) { /* forwardmode */
    int among_var;
    z->bra = z->c; /* [, line 345 */
    if (z->c + 3 >= z->l || (z->p[z->c + 3] != 132 && z->p[z->c + 3] != 167)) return 0; /* substring, line 345 */
    among_var = find_among(z, a_3, 4);
    if (!(among_var)) return 0;
    z->ket = z->c; /* ], line 345 */
    switch (among_var) { /* among, line 345 */
        case 1:
            if (!(len_utf8(z->p) > 4)) return 0; /* $(<integer expression> > <integer expression>), line 346 */
            z->B[0] = 1; /* set is_noun, line 346 */
            z->B[1] = 0; /* unset is_verb, line 346 */
            z->B[2] = 1; /* set is_defined, line 346 */
            break;
        case 2:
            if (!(len_utf8(z->p) > 3)) return 0; /* $(<integer expression> > <integer expression>), line 347 */
            z->B[0] = 1; /* set is_noun, line 347 */
            z->B[1] = 0; /* unset is_verb, line 347 */
            z->B[2] = 1; /* set is_defined, line 347 */
            break;
    }
    return 1;
}