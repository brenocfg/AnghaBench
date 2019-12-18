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
struct SN_env {int c; int lb; int l; int ket; char* p; int bra; } ;

/* Variables and functions */
 int r_RV (struct SN_env*) ; 
 int r_mark_regions (struct SN_env*) ; 
 int r_postlude (struct SN_env*) ; 
 int r_prelude (struct SN_env*) ; 
 int r_residual_form (struct SN_env*) ; 
 int r_residual_suffix (struct SN_env*) ; 
 int r_standard_suffix (struct SN_env*) ; 
 int r_verb_suffix (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

extern int portuguese_UTF_8_stem(struct SN_env * z) { /* forwardmode */
    {   int c1 = z->c; /* do, line 202 */
        {   int ret = r_prelude(z); /* call prelude, line 202 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
    lab0:
        z->c = c1;
    }
    /* do, line 203 */
    {   int ret = r_mark_regions(z); /* call mark_regions, line 203 */
        if (ret == 0) goto lab1;
        if (ret < 0) return ret;
    }
lab1:
    z->lb = z->c; z->c = z->l; /* backwards, line 204 */

    {   int m2 = z->l - z->c; (void)m2; /* do, line 205 */
        {   int m3 = z->l - z->c; (void)m3; /* or, line 209 */
            {   int m4 = z->l - z->c; (void)m4; /* and, line 207 */
                {   int m5 = z->l - z->c; (void)m5; /* or, line 206 */
                    {   int ret = r_standard_suffix(z); /* call standard_suffix, line 206 */
                        if (ret == 0) goto lab6;
                        if (ret < 0) return ret;
                    }
                    goto lab5;
                lab6:
                    z->c = z->l - m5;
                    {   int ret = r_verb_suffix(z); /* call verb_suffix, line 206 */
                        if (ret == 0) goto lab4;
                        if (ret < 0) return ret;
                    }
                }
            lab5:
                z->c = z->l - m4;
                {   int m6 = z->l - z->c; (void)m6; /* do, line 207 */
                    z->ket = z->c; /* [, line 207 */
                    if (z->c <= z->lb || z->p[z->c - 1] != 'i') goto lab7; /* literal, line 207 */
                    z->c--;
                    z->bra = z->c; /* ], line 207 */
                    {   int m_test7 = z->l - z->c; /* test, line 207 */
                        if (z->c <= z->lb || z->p[z->c - 1] != 'c') goto lab7; /* literal, line 207 */
                        z->c--;
                        z->c = z->l - m_test7;
                    }
                    {   int ret = r_RV(z); /* call RV, line 207 */
                        if (ret == 0) goto lab7;
                        if (ret < 0) return ret;
                    }
                    {   int ret = slice_del(z); /* delete, line 207 */
                        if (ret < 0) return ret;
                    }
                lab7:
                    z->c = z->l - m6;
                }
            }
            goto lab3;
        lab4:
            z->c = z->l - m3;
            {   int ret = r_residual_suffix(z); /* call residual_suffix, line 209 */
                if (ret == 0) goto lab2;
                if (ret < 0) return ret;
            }
        }
    lab3:
    lab2:
        z->c = z->l - m2;
    }
    {   int m8 = z->l - z->c; (void)m8; /* do, line 211 */
        {   int ret = r_residual_form(z); /* call residual_form, line 211 */
            if (ret == 0) goto lab8;
            if (ret < 0) return ret;
        }
    lab8:
        z->c = z->l - m8;
    }
    z->c = z->lb;
    {   int c9 = z->c; /* do, line 213 */
        {   int ret = r_postlude(z); /* call postlude, line 213 */
            if (ret == 0) goto lab9;
            if (ret < 0) return ret;
        }
    lab9:
        z->c = c9;
    }
    return 1;
}