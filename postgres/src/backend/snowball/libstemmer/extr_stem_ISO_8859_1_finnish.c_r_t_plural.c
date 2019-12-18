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
struct SN_env {int c; int* I; int lb; int ket; char* p; int bra; int l; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_9 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_V1 ; 
 scalar_t__ in_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_4 ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_t_plural(struct SN_env * z) { /* backwardmode */
    int among_var;

    {   int mlimit1; /* setlimit, line 162 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 163 */
        if (z->c <= z->lb || z->p[z->c - 1] != 't') { z->lb = mlimit1; return 0; } /* literal, line 163 */
        z->c--;
        z->bra = z->c; /* ], line 163 */
        {   int m_test2 = z->l - z->c; /* test, line 163 */
            if (in_grouping_b(z, g_V1, 97, 246, 0)) { z->lb = mlimit1; return 0; } /* grouping V1, line 163 */
            z->c = z->l - m_test2;
        }
        {   int ret = slice_del(z); /* delete, line 164 */
            if (ret < 0) return ret;
        }
        z->lb = mlimit1;
    }

    {   int mlimit3; /* setlimit, line 166 */
        if (z->c < z->I[1]) return 0;
        mlimit3 = z->lb; z->lb = z->I[1];
        z->ket = z->c; /* [, line 166 */
        if (z->c - 2 <= z->lb || z->p[z->c - 1] != 97) { z->lb = mlimit3; return 0; } /* substring, line 166 */
        among_var = find_among_b(z, a_9, 2);
        if (!(among_var)) { z->lb = mlimit3; return 0; }
        z->bra = z->c; /* ], line 166 */
        z->lb = mlimit3;
    }
    switch (among_var) { /* among, line 167 */
        case 1:
            {   int m4 = z->l - z->c; (void)m4; /* not, line 168 */
                if (!(eq_s_b(z, 2, s_4))) goto lab0; /* literal, line 168 */
                return 0;
            lab0:
                z->c = z->l - m4;
            }
            break;
    }
    {   int ret = slice_del(z); /* delete, line 171 */
        if (ret < 0) return ret;
    }
    return 1;
}