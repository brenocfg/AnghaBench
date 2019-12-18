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
struct SN_env {int c; int* I; int lb; int ket; int* p; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_0 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_s_ending ; 
 int /*<<< orphan*/  in_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_main_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;

    {   int mlimit1; /* setlimit, line 43 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 43 */
        if (z->c <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((1851440 >> (z->p[z->c - 1] & 0x1f)) & 1)) { z->lb = mlimit1; return 0; } /* substring, line 43 */
        among_var = find_among_b(z, a_0, 32);
        if (!(among_var)) { z->lb = mlimit1; return 0; }
        z->bra = z->c; /* ], line 43 */
        z->lb = mlimit1;
    }
    switch (among_var) { /* among, line 44 */
        case 1:
            {   int ret = slice_del(z); /* delete, line 50 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            if (in_grouping_b(z, g_s_ending, 97, 229, 0)) return 0; /* grouping s_ending, line 52 */
            {   int ret = slice_del(z); /* delete, line 52 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}