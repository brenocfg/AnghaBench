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
struct SN_env {int c; int bra; int ket; int l; int lb; int* I; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  eq_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int r_adjectival (struct SN_env*) ; 
 int r_derivational (struct SN_env*) ; 
 int r_mark_regions (struct SN_env*) ; 
 int r_noun (struct SN_env*) ; 
 int r_perfective_gerund (struct SN_env*) ; 
 int r_reflexive (struct SN_env*) ; 
 int r_tidy_up (struct SN_env*) ; 
 int r_verb (struct SN_env*) ; 
 int /*<<< orphan*/  s_10 ; 
 int /*<<< orphan*/  s_11 ; 
 int /*<<< orphan*/  s_9 ; 
 int skip_utf8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

extern int russian_UTF_8_stem(struct SN_env * z) { /* forwardmode */
    {   int c1 = z->c; /* do, line 205 */
        while(1) { /* repeat, line 205 */
            int c2 = z->c;
            while(1) { /* goto, line 205 */
                int c3 = z->c;
                z->bra = z->c; /* [, line 205 */
                if (!(eq_s(z, 2, s_9))) goto lab2; /* literal, line 205 */
                z->ket = z->c; /* ], line 205 */
                z->c = c3;
                break;
            lab2:
                z->c = c3;
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab1;
                    z->c = ret; /* goto, line 205 */
                }
            }
            {   int ret = slice_from_s(z, 2, s_10); /* <-, line 205 */
                if (ret < 0) return ret;
            }
            continue;
        lab1:
            z->c = c2;
            break;
        }
        z->c = c1;
    }
    /* do, line 207 */
    {   int ret = r_mark_regions(z); /* call mark_regions, line 207 */
        if (ret == 0) goto lab3;
        if (ret < 0) return ret;
    }
lab3:
    z->lb = z->c; z->c = z->l; /* backwards, line 208 */


    {   int mlimit4; /* setlimit, line 208 */
        if (z->c < z->I[0]) return 0;
        mlimit4 = z->lb; z->lb = z->I[0];
        {   int m5 = z->l - z->c; (void)m5; /* do, line 209 */
            {   int m6 = z->l - z->c; (void)m6; /* or, line 210 */
                {   int ret = r_perfective_gerund(z); /* call perfective_gerund, line 210 */
                    if (ret == 0) goto lab6;
                    if (ret < 0) return ret;
                }
                goto lab5;
            lab6:
                z->c = z->l - m6;
                {   int m7 = z->l - z->c; (void)m7; /* try, line 211 */
                    {   int ret = r_reflexive(z); /* call reflexive, line 211 */
                        if (ret == 0) { z->c = z->l - m7; goto lab7; }
                        if (ret < 0) return ret;
                    }
                lab7:
                    ;
                }
                {   int m8 = z->l - z->c; (void)m8; /* or, line 212 */
                    {   int ret = r_adjectival(z); /* call adjectival, line 212 */
                        if (ret == 0) goto lab9;
                        if (ret < 0) return ret;
                    }
                    goto lab8;
                lab9:
                    z->c = z->l - m8;
                    {   int ret = r_verb(z); /* call verb, line 212 */
                        if (ret == 0) goto lab10;
                        if (ret < 0) return ret;
                    }
                    goto lab8;
                lab10:
                    z->c = z->l - m8;
                    {   int ret = r_noun(z); /* call noun, line 212 */
                        if (ret == 0) goto lab4;
                        if (ret < 0) return ret;
                    }
                }
            lab8:
                ;
            }
        lab5:
        lab4:
            z->c = z->l - m5;
        }
        {   int m9 = z->l - z->c; (void)m9; /* try, line 215 */
            z->ket = z->c; /* [, line 215 */
            if (!(eq_s_b(z, 2, s_11))) { z->c = z->l - m9; goto lab11; } /* literal, line 215 */
            z->bra = z->c; /* ], line 215 */
            {   int ret = slice_del(z); /* delete, line 215 */
                if (ret < 0) return ret;
            }
        lab11:
            ;
        }
        {   int m10 = z->l - z->c; (void)m10; /* do, line 218 */
            {   int ret = r_derivational(z); /* call derivational, line 218 */
                if (ret == 0) goto lab12;
                if (ret < 0) return ret;
            }
        lab12:
            z->c = z->l - m10;
        }
        {   int m11 = z->l - z->c; (void)m11; /* do, line 219 */
            {   int ret = r_tidy_up(z); /* call tidy_up, line 219 */
                if (ret == 0) goto lab13;
                if (ret < 0) return ret;
            }
        lab13:
            z->c = z->l - m11;
        }
        z->lb = mlimit4;
    }
    z->c = z->lb;
    return 1;
}