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
struct SN_env {int ket; int c; int* B; int l; int bra; } ;

/* Variables and functions */
 int r_mark_DUr (struct SN_env*) ; 
 int r_mark_cAsInA (struct SN_env*) ; 
 int r_mark_lAr (struct SN_env*) ; 
 int r_mark_nUz (struct SN_env*) ; 
 int r_mark_sUn (struct SN_env*) ; 
 int r_mark_sUnUz (struct SN_env*) ; 
 int r_mark_yDU (struct SN_env*) ; 
 int r_mark_yUm (struct SN_env*) ; 
 int r_mark_yUz (struct SN_env*) ; 
 int r_mark_yken (struct SN_env*) ; 
 int r_mark_ymUs_ (struct SN_env*) ; 
 int r_mark_ysA (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_stem_nominal_verb_suffixes(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 310 */
    z->B[0] = 1; /* set continue_stemming_noun_suffixes, line 311 */
    {   int m1 = z->l - z->c; (void)m1; /* or, line 313 */
        {   int m2 = z->l - z->c; (void)m2; /* or, line 312 */
            {   int ret = r_mark_ymUs_(z); /* call mark_ymUs_, line 312 */
                if (ret == 0) goto lab3;
                if (ret < 0) return ret;
            }
            goto lab2;
        lab3:
            z->c = z->l - m2;
            {   int ret = r_mark_yDU(z); /* call mark_yDU, line 312 */
                if (ret == 0) goto lab4;
                if (ret < 0) return ret;
            }
            goto lab2;
        lab4:
            z->c = z->l - m2;
            {   int ret = r_mark_ysA(z); /* call mark_ysA, line 312 */
                if (ret == 0) goto lab5;
                if (ret < 0) return ret;
            }
            goto lab2;
        lab5:
            z->c = z->l - m2;
            {   int ret = r_mark_yken(z); /* call mark_yken, line 312 */
                if (ret == 0) goto lab1;
                if (ret < 0) return ret;
            }
        }
    lab2:
        goto lab0;
    lab1:
        z->c = z->l - m1;
        {   int ret = r_mark_cAsInA(z); /* call mark_cAsInA, line 314 */
            if (ret == 0) goto lab6;
            if (ret < 0) return ret;
        }
        {   int m3 = z->l - z->c; (void)m3; /* or, line 314 */
            {   int ret = r_mark_sUnUz(z); /* call mark_sUnUz, line 314 */
                if (ret == 0) goto lab8;
                if (ret < 0) return ret;
            }
            goto lab7;
        lab8:
            z->c = z->l - m3;
            {   int ret = r_mark_lAr(z); /* call mark_lAr, line 314 */
                if (ret == 0) goto lab9;
                if (ret < 0) return ret;
            }
            goto lab7;
        lab9:
            z->c = z->l - m3;
            {   int ret = r_mark_yUm(z); /* call mark_yUm, line 314 */
                if (ret == 0) goto lab10;
                if (ret < 0) return ret;
            }
            goto lab7;
        lab10:
            z->c = z->l - m3;
            {   int ret = r_mark_sUn(z); /* call mark_sUn, line 314 */
                if (ret == 0) goto lab11;
                if (ret < 0) return ret;
            }
            goto lab7;
        lab11:
            z->c = z->l - m3;
            {   int ret = r_mark_yUz(z); /* call mark_yUz, line 314 */
                if (ret == 0) goto lab12;
                if (ret < 0) return ret;
            }
            goto lab7;
        lab12:
            z->c = z->l - m3;
        }
    lab7:
        {   int ret = r_mark_ymUs_(z); /* call mark_ymUs_, line 314 */
            if (ret == 0) goto lab6;
            if (ret < 0) return ret;
        }
        goto lab0;
    lab6:
        z->c = z->l - m1;
        {   int ret = r_mark_lAr(z); /* call mark_lAr, line 317 */
            if (ret == 0) goto lab13;
            if (ret < 0) return ret;
        }
        z->bra = z->c; /* ], line 317 */
        {   int ret = slice_del(z); /* delete, line 317 */
            if (ret < 0) return ret;
        }
        {   int m4 = z->l - z->c; (void)m4; /* try, line 317 */
            z->ket = z->c; /* [, line 317 */
            {   int m5 = z->l - z->c; (void)m5; /* or, line 317 */
                {   int ret = r_mark_DUr(z); /* call mark_DUr, line 317 */
                    if (ret == 0) goto lab16;
                    if (ret < 0) return ret;
                }
                goto lab15;
            lab16:
                z->c = z->l - m5;
                {   int ret = r_mark_yDU(z); /* call mark_yDU, line 317 */
                    if (ret == 0) goto lab17;
                    if (ret < 0) return ret;
                }
                goto lab15;
            lab17:
                z->c = z->l - m5;
                {   int ret = r_mark_ysA(z); /* call mark_ysA, line 317 */
                    if (ret == 0) goto lab18;
                    if (ret < 0) return ret;
                }
                goto lab15;
            lab18:
                z->c = z->l - m5;
                {   int ret = r_mark_ymUs_(z); /* call mark_ymUs_, line 317 */
                    if (ret == 0) { z->c = z->l - m4; goto lab14; }
                    if (ret < 0) return ret;
                }
            }
        lab15:
        lab14:
            ;
        }
        z->B[0] = 0; /* unset continue_stemming_noun_suffixes, line 318 */
        goto lab0;
    lab13:
        z->c = z->l - m1;
        {   int ret = r_mark_nUz(z); /* call mark_nUz, line 321 */
            if (ret == 0) goto lab19;
            if (ret < 0) return ret;
        }
        {   int m6 = z->l - z->c; (void)m6; /* or, line 321 */
            {   int ret = r_mark_yDU(z); /* call mark_yDU, line 321 */
                if (ret == 0) goto lab21;
                if (ret < 0) return ret;
            }
            goto lab20;
        lab21:
            z->c = z->l - m6;
            {   int ret = r_mark_ysA(z); /* call mark_ysA, line 321 */
                if (ret == 0) goto lab19;
                if (ret < 0) return ret;
            }
        }
    lab20:
        goto lab0;
    lab19:
        z->c = z->l - m1;
        {   int m7 = z->l - z->c; (void)m7; /* or, line 323 */
            {   int ret = r_mark_sUnUz(z); /* call mark_sUnUz, line 323 */
                if (ret == 0) goto lab24;
                if (ret < 0) return ret;
            }
            goto lab23;
        lab24:
            z->c = z->l - m7;
            {   int ret = r_mark_yUz(z); /* call mark_yUz, line 323 */
                if (ret == 0) goto lab25;
                if (ret < 0) return ret;
            }
            goto lab23;
        lab25:
            z->c = z->l - m7;
            {   int ret = r_mark_sUn(z); /* call mark_sUn, line 323 */
                if (ret == 0) goto lab26;
                if (ret < 0) return ret;
            }
            goto lab23;
        lab26:
            z->c = z->l - m7;
            {   int ret = r_mark_yUm(z); /* call mark_yUm, line 323 */
                if (ret == 0) goto lab22;
                if (ret < 0) return ret;
            }
        }
    lab23:
        z->bra = z->c; /* ], line 323 */
        {   int ret = slice_del(z); /* delete, line 323 */
            if (ret < 0) return ret;
        }
        {   int m8 = z->l - z->c; (void)m8; /* try, line 323 */
            z->ket = z->c; /* [, line 323 */
            {   int ret = r_mark_ymUs_(z); /* call mark_ymUs_, line 323 */
                if (ret == 0) { z->c = z->l - m8; goto lab27; }
                if (ret < 0) return ret;
            }
        lab27:
            ;
        }
        goto lab0;
    lab22:
        z->c = z->l - m1;
        {   int ret = r_mark_DUr(z); /* call mark_DUr, line 325 */
            if (ret <= 0) return ret;
        }
        z->bra = z->c; /* ], line 325 */
        {   int ret = slice_del(z); /* delete, line 325 */
            if (ret < 0) return ret;
        }
        {   int m9 = z->l - z->c; (void)m9; /* try, line 325 */
            z->ket = z->c; /* [, line 325 */
            {   int m10 = z->l - z->c; (void)m10; /* or, line 325 */
                {   int ret = r_mark_sUnUz(z); /* call mark_sUnUz, line 325 */
                    if (ret == 0) goto lab30;
                    if (ret < 0) return ret;
                }
                goto lab29;
            lab30:
                z->c = z->l - m10;
                {   int ret = r_mark_lAr(z); /* call mark_lAr, line 325 */
                    if (ret == 0) goto lab31;
                    if (ret < 0) return ret;
                }
                goto lab29;
            lab31:
                z->c = z->l - m10;
                {   int ret = r_mark_yUm(z); /* call mark_yUm, line 325 */
                    if (ret == 0) goto lab32;
                    if (ret < 0) return ret;
                }
                goto lab29;
            lab32:
                z->c = z->l - m10;
                {   int ret = r_mark_sUn(z); /* call mark_sUn, line 325 */
                    if (ret == 0) goto lab33;
                    if (ret < 0) return ret;
                }
                goto lab29;
            lab33:
                z->c = z->l - m10;
                {   int ret = r_mark_yUz(z); /* call mark_yUz, line 325 */
                    if (ret == 0) goto lab34;
                    if (ret < 0) return ret;
                }
                goto lab29;
            lab34:
                z->c = z->l - m10;
            }
        lab29:
            {   int ret = r_mark_ymUs_(z); /* call mark_ymUs_, line 325 */
                if (ret == 0) { z->c = z->l - m9; goto lab28; }
                if (ret < 0) return ret;
            }
        lab28:
            ;
        }
    }
lab0:
    z->bra = z->c; /* ], line 326 */
    {   int ret = slice_del(z); /* delete, line 326 */
        if (ret < 0) return ret;
    }
    return 1;
}