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
struct SN_env {int* B; int c; int bra; int l; char* p; size_t ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_v ; 
 scalar_t__ in_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_0 ; 
 int /*<<< orphan*/  s_1 ; 
 int skip_utf8 (char*,int,int /*<<< orphan*/ ,int,int) ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_prelude(struct SN_env * z) { /* forwardmode */
    z->B[0] = 0; /* unset Y_found, line 26 */
    {   int c1 = z->c; /* do, line 27 */
        z->bra = z->c; /* [, line 27 */
        if (z->c == z->l || z->p[z->c] != '\'') goto lab0; /* literal, line 27 */
        z->c++;
        z->ket = z->c; /* ], line 27 */
        {   int ret = slice_del(z); /* delete, line 27 */
            if (ret < 0) return ret;
        }
    lab0:
        z->c = c1;
    }
    {   int c2 = z->c; /* do, line 28 */
        z->bra = z->c; /* [, line 28 */
        if (z->c == z->l || z->p[z->c] != 'y') goto lab1; /* literal, line 28 */
        z->c++;
        z->ket = z->c; /* ], line 28 */
        {   int ret = slice_from_s(z, 1, s_0); /* <-, line 28 */
            if (ret < 0) return ret;
        }
        z->B[0] = 1; /* set Y_found, line 28 */
    lab1:
        z->c = c2;
    }
    {   int c3 = z->c; /* do, line 29 */
        while(1) { /* repeat, line 29 */
            int c4 = z->c;
            while(1) { /* goto, line 29 */
                int c5 = z->c;
                if (in_grouping_U(z, g_v, 97, 121, 0)) goto lab4; /* grouping v, line 29 */
                z->bra = z->c; /* [, line 29 */
                if (z->c == z->l || z->p[z->c] != 'y') goto lab4; /* literal, line 29 */
                z->c++;
                z->ket = z->c; /* ], line 29 */
                z->c = c5;
                break;
            lab4:
                z->c = c5;
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab3;
                    z->c = ret; /* goto, line 29 */
                }
            }
            {   int ret = slice_from_s(z, 1, s_1); /* <-, line 29 */
                if (ret < 0) return ret;
            }
            z->B[0] = 1; /* set Y_found, line 29 */
            continue;
        lab3:
            z->c = c4;
            break;
        }
        z->c = c3;
    }
    return 1;
}