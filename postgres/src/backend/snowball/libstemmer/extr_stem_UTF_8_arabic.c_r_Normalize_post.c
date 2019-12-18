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
struct SN_env {int c; int lb; int l; int ket; int* p; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_1 ; 
 int /*<<< orphan*/  a_2 ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_50 ; 
 int /*<<< orphan*/  s_51 ; 
 int /*<<< orphan*/  s_52 ; 
 int /*<<< orphan*/  s_53 ; 
 int skip_utf8 (int*,int,int /*<<< orphan*/ ,int,int) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Normalize_post(struct SN_env * z) { /* forwardmode */
    int among_var;
    {   int c1 = z->c; /* do, line 318 */
        z->lb = z->c; z->c = z->l; /* backwards, line 320 */

        z->ket = z->c; /* [, line 321 */
        if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 5 || !((124 >> (z->p[z->c - 1] & 0x1f)) & 1)) goto lab0; /* substring, line 321 */
        if (!(find_among_b(z, a_1, 5))) goto lab0;
        z->bra = z->c; /* ], line 321 */
        {   int ret = slice_from_s(z, 2, s_50); /* <-, line 322 */
            if (ret < 0) return ret;
        }
        z->c = z->lb;
    lab0:
        z->c = c1;
    }
    {   int c2 = z->c; /* do, line 329 */
        while(1) { /* repeat, line 329 */
            int c3 = z->c;
            {   int c4 = z->c; /* or, line 338 */
                z->bra = z->c; /* [, line 332 */
                if (z->c + 1 >= z->l || z->p[z->c + 1] >> 5 != 5 || !((124 >> (z->p[z->c + 1] & 0x1f)) & 1)) goto lab4; /* substring, line 332 */
                among_var = find_among(z, a_2, 5);
                if (!(among_var)) goto lab4;
                z->ket = z->c; /* ], line 332 */
                switch (among_var) { /* among, line 332 */
                    case 1:
                        {   int ret = slice_from_s(z, 2, s_51); /* <-, line 333 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 2:
                        {   int ret = slice_from_s(z, 2, s_52); /* <-, line 334 */
                            if (ret < 0) return ret;
                        }
                        break;
                    case 3:
                        {   int ret = slice_from_s(z, 2, s_53); /* <-, line 335 */
                            if (ret < 0) return ret;
                        }
                        break;
                }
                goto lab3;
            lab4:
                z->c = c4;
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab2;
                    z->c = ret; /* next, line 339 */
                }
            }
        lab3:
            continue;
        lab2:
            z->c = c3;
            break;
        }
        z->c = c2;
    }
    return 1;
}