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
struct SN_env {scalar_t__ c; scalar_t__* I; int lb; scalar_t__ ket; scalar_t__ bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_0 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_particle_end ; 
 int /*<<< orphan*/  in_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int r_R2 (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_particle_etc(struct SN_env * z) { /* backwardmode */
    int among_var;

    {   int mlimit1; /* setlimit, line 56 */
        if (z->c < z->I[0]) return 0;
        mlimit1 = z->lb; z->lb = z->I[0];
        z->ket = z->c; /* [, line 56 */
        among_var = find_among_b(z, a_0, 10); /* substring, line 56 */
        if (!(among_var)) { z->lb = mlimit1; return 0; }
        z->bra = z->c; /* ], line 56 */
        z->lb = mlimit1;
    }
    switch (among_var) { /* among, line 57 */
        case 1:
            if (in_grouping_b_U(z, g_particle_end, 97, 246, 0)) return 0; /* grouping particle_end, line 63 */
            break;
        case 2:
            {   int ret = r_R2(z); /* call R2, line 65 */
                if (ret <= 0) return ret;
            }
            break;
    }
    {   int ret = slice_del(z); /* delete, line 67 */
        if (ret < 0) return ret;
    }
    return 1;
}