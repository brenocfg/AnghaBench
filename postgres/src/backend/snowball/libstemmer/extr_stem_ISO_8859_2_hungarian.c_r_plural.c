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
 int /*<<< orphan*/  a_8 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int /*<<< orphan*/  s_6 ; 
 int /*<<< orphan*/  s_7 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_plural(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 142 */
    if (z->c <= z->lb || z->p[z->c - 1] != 107) return 0; /* substring, line 142 */
    among_var = find_among_b(z, a_8, 7);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 142 */
    {   int ret = r_R1(z); /* call R1, line 142 */
        if (ret <= 0) return ret;
    }
    switch (among_var) { /* among, line 142 */
        case 1:
            {   int ret = slice_from_s(z, 1, s_6); /* <-, line 143 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 1, s_7); /* <-, line 144 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_del(z); /* delete, line 145 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}