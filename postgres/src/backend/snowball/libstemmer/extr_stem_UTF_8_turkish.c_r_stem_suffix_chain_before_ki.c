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
struct SN_env {int ket; int c; int l; int bra; } ;

/* Variables and functions */
 int r_mark_DA (struct SN_env*) ; 
 int r_mark_ki (struct SN_env*) ; 
 int r_mark_lAr (struct SN_env*) ; 
 int r_mark_lArI (struct SN_env*) ; 
 int r_mark_nUn (struct SN_env*) ; 
 int r_mark_ndA (struct SN_env*) ; 
 int r_mark_possessives (struct SN_env*) ; 
 int r_mark_sU (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_stem_suffix_chain_before_ki(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 331 */
    {   int ret = r_mark_ki(z); /* call mark_ki, line 332 */
        if (ret <= 0) return ret;
    }
    {   int m1 = z->l - z->c; (void)m1; /* or, line 340 */
        {   int ret = r_mark_DA(z); /* call mark_DA, line 334 */
            if (ret == 0) goto lab1;
            if (ret < 0) return ret;
        }
        z->bra = z->c; /* ], line 334 */
        {   int ret = slice_del(z); /* delete, line 334 */
            if (ret < 0) return ret;
        }
        {   int m2 = z->l - z->c; (void)m2; /* try, line 334 */
            z->ket = z->c; /* [, line 334 */
            {   int m3 = z->l - z->c; (void)m3; /* or, line 336 */
                {   int ret = r_mark_lAr(z); /* call mark_lAr, line 335 */
                    if (ret == 0) goto lab4;
                    if (ret < 0) return ret;
                }
                z->bra = z->c; /* ], line 335 */
                {   int ret = slice_del(z); /* delete, line 335 */
                    if (ret < 0) return ret;
                }
                {   int m4 = z->l - z->c; (void)m4; /* try, line 335 */
                    {   int ret = r_stem_suffix_chain_before_ki(z); /* call stem_suffix_chain_before_ki, line 335 */
                        if (ret == 0) { z->c = z->l - m4; goto lab5; }
                        if (ret < 0) return ret;
                    }
                lab5:
                    ;
                }
                goto lab3;
            lab4:
                z->c = z->l - m3;
                {   int ret = r_mark_possessives(z); /* call mark_possessives, line 337 */
                    if (ret == 0) { z->c = z->l - m2; goto lab2; }
                    if (ret < 0) return ret;
                }
                z->bra = z->c; /* ], line 337 */
                {   int ret = slice_del(z); /* delete, line 337 */
                    if (ret < 0) return ret;
                }
                {   int m5 = z->l - z->c; (void)m5; /* try, line 337 */
                    z->ket = z->c; /* [, line 337 */
                    {   int ret = r_mark_lAr(z); /* call mark_lAr, line 337 */
                        if (ret == 0) { z->c = z->l - m5; goto lab6; }
                        if (ret < 0) return ret;
                    }
                    z->bra = z->c; /* ], line 337 */
                    {   int ret = slice_del(z); /* delete, line 337 */
                        if (ret < 0) return ret;
                    }
                    {   int ret = r_stem_suffix_chain_before_ki(z); /* call stem_suffix_chain_before_ki, line 337 */
                        if (ret == 0) { z->c = z->l - m5; goto lab6; }
                        if (ret < 0) return ret;
                    }
                lab6:
                    ;
                }
            }
        lab3:
        lab2:
            ;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        {   int ret = r_mark_nUn(z); /* call mark_nUn, line 341 */
            if (ret == 0) goto lab7;
            if (ret < 0) return ret;
        }
        z->bra = z->c; /* ], line 341 */
        {   int ret = slice_del(z); /* delete, line 341 */
            if (ret < 0) return ret;
        }
        {   int m6 = z->l - z->c; (void)m6; /* try, line 341 */
            z->ket = z->c; /* [, line 341 */
            {   int m7 = z->l - z->c; (void)m7; /* or, line 343 */
                {   int ret = r_mark_lArI(z); /* call mark_lArI, line 342 */
                    if (ret == 0) goto lab10;
                    if (ret < 0) return ret;
                }
                z->bra = z->c; /* ], line 342 */
                {   int ret = slice_del(z); /* delete, line 342 */
                    if (ret < 0) return ret;
                }
                goto lab9;
            lab10:
                z->c = z->l - m7;
                z->ket = z->c; /* [, line 344 */
                {   int m8 = z->l - z->c; (void)m8; /* or, line 344 */
                    {   int ret = r_mark_possessives(z); /* call mark_possessives, line 344 */
                        if (ret == 0) goto lab13;
                        if (ret < 0) return ret;
                    }
                    goto lab12;
                lab13:
                    z->c = z->l - m8;
                    {   int ret = r_mark_sU(z); /* call mark_sU, line 344 */
                        if (ret == 0) goto lab11;
                        if (ret < 0) return ret;
                    }
                }
            lab12:
                z->bra = z->c; /* ], line 344 */
                {   int ret = slice_del(z); /* delete, line 344 */
                    if (ret < 0) return ret;
                }
                {   int m9 = z->l - z->c; (void)m9; /* try, line 344 */
                    z->ket = z->c; /* [, line 344 */
                    {   int ret = r_mark_lAr(z); /* call mark_lAr, line 344 */
                        if (ret == 0) { z->c = z->l - m9; goto lab14; }
                        if (ret < 0) return ret;
                    }
                    z->bra = z->c; /* ], line 344 */
                    {   int ret = slice_del(z); /* delete, line 344 */
                        if (ret < 0) return ret;
                    }
                    {   int ret = r_stem_suffix_chain_before_ki(z); /* call stem_suffix_chain_before_ki, line 344 */
                        if (ret == 0) { z->c = z->l - m9; goto lab14; }
                        if (ret < 0) return ret;
                    }
                lab14:
                    ;
                }
                goto lab9;
            lab11:
                z->c = z->l - m7;
                {   int ret = r_stem_suffix_chain_before_ki(z); /* call stem_suffix_chain_before_ki, line 346 */
                    if (ret == 0) { z->c = z->l - m6; goto lab8; }
                    if (ret < 0) return ret;
                }
            }
        lab9:
        lab8:
            ;
        }
        goto lab0;
    lab7:
        z->c = z->l - m1;
        {   int ret = r_mark_ndA(z); /* call mark_ndA, line 349 */
            if (ret <= 0) return ret;
        }
        {   int m10 = z->l - z->c; (void)m10; /* or, line 351 */
            {   int ret = r_mark_lArI(z); /* call mark_lArI, line 350 */
                if (ret == 0) goto lab16;
                if (ret < 0) return ret;
            }
            z->bra = z->c; /* ], line 350 */
            {   int ret = slice_del(z); /* delete, line 350 */
                if (ret < 0) return ret;
            }
            goto lab15;
        lab16:
            z->c = z->l - m10;
            {   int ret = r_mark_sU(z); /* call mark_sU, line 352 */
                if (ret == 0) goto lab17;
                if (ret < 0) return ret;
            }
            z->bra = z->c; /* ], line 352 */
            {   int ret = slice_del(z); /* delete, line 352 */
                if (ret < 0) return ret;
            }
            {   int m11 = z->l - z->c; (void)m11; /* try, line 352 */
                z->ket = z->c; /* [, line 352 */
                {   int ret = r_mark_lAr(z); /* call mark_lAr, line 352 */
                    if (ret == 0) { z->c = z->l - m11; goto lab18; }
                    if (ret < 0) return ret;
                }
                z->bra = z->c; /* ], line 352 */
                {   int ret = slice_del(z); /* delete, line 352 */
                    if (ret < 0) return ret;
                }
                {   int ret = r_stem_suffix_chain_before_ki(z); /* call stem_suffix_chain_before_ki, line 352 */
                    if (ret == 0) { z->c = z->l - m11; goto lab18; }
                    if (ret < 0) return ret;
                }
            lab18:
                ;
            }
            goto lab15;
        lab17:
            z->c = z->l - m10;
            {   int ret = r_stem_suffix_chain_before_ki(z); /* call stem_suffix_chain_before_ki, line 354 */
                if (ret <= 0) return ret;
            }
        }
    lab15:
        ;
    }
lab0:
    return 1;
}