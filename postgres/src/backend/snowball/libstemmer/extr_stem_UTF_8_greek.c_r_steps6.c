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
struct SN_env {int ket; int c; int bra; int l; int lb; int* p; scalar_t__* S; scalar_t__* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_15 ; 
 int /*<<< orphan*/  a_16 ; 
 int /*<<< orphan*/  a_17 ; 
 int /*<<< orphan*/  a_18 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_45 ; 
 int /*<<< orphan*/  s_46 ; 
 int /*<<< orphan*/  s_47 ; 
 int /*<<< orphan*/  s_48 ; 
 int /*<<< orphan*/  s_49 ; 
 int /*<<< orphan*/  s_50 ; 
 int /*<<< orphan*/  s_51 ; 
 int /*<<< orphan*/  s_52 ; 
 int /*<<< orphan*/  s_53 ; 
 int /*<<< orphan*/  s_54 ; 
 int /*<<< orphan*/  s_55 ; 
 int /*<<< orphan*/  s_56 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 void* slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_steps6(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 273 */
    if (!(find_among_b(z, a_18, 6))) return 0; /* substring, line 273 */
    z->bra = z->c; /* ], line 273 */
    {   int ret = slice_del(z); /* delete, line 275 */
        if (ret < 0) return ret;
    }
    z->B[0] = 0; /* unset test1, line 276 */
    {   int m1 = z->l - z->c; (void)m1; /* or, line 280 */
        z->ket = z->c; /* [, line 277 */
        if (z->c - 3 <= z->lb || z->p[z->c - 1] != 181) goto lab1; /* substring, line 277 */
        if (!(find_among_b(z, a_15, 5))) goto lab1;
        z->bra = z->c; /* ], line 277 */
        if (z->c > z->lb) goto lab1; /* atlimit, line 277 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 279 */
        if (z->S[0] == 0) return -1; /* -> s, line 279 */
        {   int ret = slice_from_s(z, 6, s_45); /* <-, line 279 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 279 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        z->ket = z->c; /* [, line 281 */
        if (z->c - 7 <= z->lb || z->p[z->c - 1] != 181) goto lab2; /* substring, line 281 */
        if (!(find_among_b(z, a_16, 2))) goto lab2;
        z->bra = z->c; /* ], line 281 */
        if (z->c > z->lb) goto lab2; /* atlimit, line 281 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 283 */
        if (z->S[0] == 0) return -1; /* -> s, line 283 */
        {   int ret = slice_from_s(z, 2, s_46); /* <-, line 283 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 283 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab0;
    lab2:
        z->c = z->l - m1;
        z->ket = z->c; /* [, line 285 */
        if (z->c - 9 <= z->lb || (z->p[z->c - 1] != 186 && z->p[z->c - 1] != 189)) return 0; /* substring, line 285 */
        among_var = find_among_b(z, a_17, 10);
        if (!(among_var)) return 0;
        z->bra = z->c; /* ], line 285 */
        switch (among_var) { /* among, line 285 */
            case 1:
                {   int ret = slice_from_s(z, 12, s_47); /* <-, line 286 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_from_s(z, 8, s_48); /* <-, line 287 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = slice_from_s(z, 10, s_49); /* <-, line 288 */
                    if (ret < 0) return ret;
                }
                break;
            case 4:
                {   int ret = slice_from_s(z, 6, s_50); /* <-, line 289 */
                    if (ret < 0) return ret;
                }
                break;
            case 5:
                {   int ret = slice_from_s(z, 12, s_51); /* <-, line 290 */
                    if (ret < 0) return ret;
                }
                break;
            case 6:
                {   int ret = slice_from_s(z, 10, s_52); /* <-, line 291 */
                    if (ret < 0) return ret;
                }
                break;
            case 7:
                {   int ret = slice_from_s(z, 6, s_53); /* <-, line 292 */
                    if (ret < 0) return ret;
                }
                break;
            case 8:
                {   int ret = slice_from_s(z, 16, s_54); /* <-, line 293 */
                    if (ret < 0) return ret;
                }
                break;
            case 9:
                {   int ret = slice_from_s(z, 12, s_55); /* <-, line 294 */
                    if (ret < 0) return ret;
                }
                break;
            case 10:
                {   int ret = slice_from_s(z, 10, s_56); /* <-, line 295 */
                    if (ret < 0) return ret;
                }
                break;
        }
    }
lab0:
    return 1;
}