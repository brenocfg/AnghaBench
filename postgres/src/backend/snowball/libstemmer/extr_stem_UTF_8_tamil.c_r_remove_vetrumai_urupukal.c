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
struct SN_env {int* B; int lb; int c; int l; int ket; int bra; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_18 ; 
 int /*<<< orphan*/  a_19 ; 
 int /*<<< orphan*/  a_20 ; 
 int /*<<< orphan*/  a_21 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int len_utf8 (int /*<<< orphan*/ ) ; 
 int r_fix_endings (struct SN_env*) ; 
 int r_has_min_length (struct SN_env*) ; 
 int /*<<< orphan*/  s_100 ; 
 int /*<<< orphan*/  s_101 ; 
 int /*<<< orphan*/  s_102 ; 
 int /*<<< orphan*/  s_103 ; 
 int /*<<< orphan*/  s_71 ; 
 int /*<<< orphan*/  s_72 ; 
 int /*<<< orphan*/  s_73 ; 
 int /*<<< orphan*/  s_74 ; 
 int /*<<< orphan*/  s_75 ; 
 int /*<<< orphan*/  s_76 ; 
 int /*<<< orphan*/  s_77 ; 
 int /*<<< orphan*/  s_78 ; 
 int /*<<< orphan*/  s_79 ; 
 int /*<<< orphan*/  s_80 ; 
 int /*<<< orphan*/  s_81 ; 
 int /*<<< orphan*/  s_82 ; 
 int /*<<< orphan*/  s_83 ; 
 int /*<<< orphan*/  s_84 ; 
 int /*<<< orphan*/  s_85 ; 
 int /*<<< orphan*/  s_86 ; 
 int /*<<< orphan*/  s_87 ; 
 int /*<<< orphan*/  s_88 ; 
 int /*<<< orphan*/  s_89 ; 
 int /*<<< orphan*/  s_90 ; 
 int /*<<< orphan*/  s_91 ; 
 int /*<<< orphan*/  s_92 ; 
 int /*<<< orphan*/  s_93 ; 
 int /*<<< orphan*/  s_94 ; 
 int /*<<< orphan*/  s_95 ; 
 int /*<<< orphan*/  s_96 ; 
 int /*<<< orphan*/  s_97 ; 
 int /*<<< orphan*/  s_98 ; 
 int /*<<< orphan*/  s_99 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_remove_vetrumai_urupukal(struct SN_env * z) { /* forwardmode */
    z->B[0] = 0; /* unset found_a_match, line 253 */
    z->B[1] = 0; /* unset found_vetrumai_urupu, line 254 */
    {   int ret = r_has_min_length(z); /* call has_min_length, line 255 */
        if (ret <= 0) return ret;
    }
    z->lb = z->c; z->c = z->l; /* backwards, line 256 */

    {   int m1 = z->l - z->c; (void)m1; /* or, line 259 */
        {   int m_test2 = z->l - z->c; /* test, line 258 */
            z->ket = z->c; /* [, line 258 */
            if (!(eq_s_b(z, 6, s_71))) goto lab1; /* literal, line 258 */
            z->bra = z->c; /* ], line 258 */
            {   int ret = slice_del(z); /* delete, line 258 */
                if (ret < 0) return ret;
            }
            z->c = z->l - m_test2;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        {   int m_test3 = z->l - z->c; /* test, line 260 */
            z->ket = z->c; /* [, line 260 */
            {   int m4 = z->l - z->c; (void)m4; /* or, line 261 */
                {   int m5 = z->l - z->c; (void)m5; /* or, line 260 */
                    if (!(eq_s_b(z, 9, s_72))) goto lab6; /* literal, line 260 */
                    goto lab5;
                lab6:
                    z->c = z->l - m5;
                    if (!(eq_s_b(z, 3, s_73))) goto lab4; /* literal, line 261 */
                }
            lab5:
                {   int m_test6 = z->l - z->c; /* test, line 261 */
                    {   int m7 = z->l - z->c; (void)m7; /* not, line 261 */
                        if (!(find_among_b(z, a_18, 6))) goto lab7; /* among, line 261 */
                        goto lab4;
                    lab7:
                        z->c = z->l - m7;
                    }
                    z->c = z->l - m_test6;
                }
                goto lab3;
            lab4:
                z->c = z->l - m4;
                if (!(eq_s_b(z, 3, s_74))) goto lab2; /* literal, line 262 */
                {   int m_test8 = z->l - z->c; /* test, line 262 */
                    if (!(find_among_b(z, a_19, 6))) goto lab2; /* among, line 262 */
                    if (!(eq_s_b(z, 3, s_75))) goto lab2; /* literal, line 262 */
                    z->c = z->l - m_test8;
                }
            }
        lab3:
            z->bra = z->c; /* ], line 263 */
            {   int ret = slice_from_s(z, 3, s_76); /* <-, line 263 */
                if (ret < 0) return ret;
            }
            z->c = z->l - m_test3;
        }
        goto lab0;
    lab2:
        z->c = z->l - m1;
        {   int m_test9 = z->l - z->c; /* test, line 266 */
            z->ket = z->c; /* [, line 266 */
            {   int m10 = z->l - z->c; (void)m10; /* or, line 267 */
                if (!(eq_s_b(z, 9, s_77))) goto lab10; /* literal, line 267 */
                goto lab9;
            lab10:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 9, s_78))) goto lab11; /* literal, line 268 */
                goto lab9;
            lab11:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 9, s_79))) goto lab12; /* literal, line 269 */
                goto lab9;
            lab12:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 9, s_80))) goto lab13; /* literal, line 270 */
                goto lab9;
            lab13:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 9, s_81))) goto lab14; /* literal, line 271 */
                {   int m_test11 = z->l - z->c; /* test, line 271 */
                    {   int m12 = z->l - z->c; (void)m12; /* not, line 271 */
                        if (!(eq_s_b(z, 3, s_82))) goto lab15; /* literal, line 271 */
                        goto lab14;
                    lab15:
                        z->c = z->l - m12;
                    }
                    z->c = z->l - m_test11;
                }
                goto lab9;
            lab14:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 15, s_83))) goto lab16; /* literal, line 272 */
                goto lab9;
            lab16:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 21, s_84))) goto lab17; /* literal, line 273 */
                goto lab9;
            lab17:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 9, s_85))) goto lab18; /* literal, line 274 */
                goto lab9;
            lab18:
                z->c = z->l - m10;
                if (!(len_utf8(z->p) >= 7)) goto lab19; /* $(<integer expression> >= <integer expression>), line 275 */
                if (!(eq_s_b(z, 12, s_86))) goto lab19; /* literal, line 275 */
                goto lab9;
            lab19:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 9, s_87))) goto lab20; /* literal, line 276 */
                goto lab9;
            lab20:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 9, s_88))) goto lab21; /* literal, line 277 */
                goto lab9;
            lab21:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 12, s_89))) goto lab22; /* literal, line 278 */
                goto lab9;
            lab22:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 6, s_90))) goto lab23; /* literal, line 279 */
                {   int m_test13 = z->l - z->c; /* test, line 279 */
                    {   int m14 = z->l - z->c; (void)m14; /* not, line 279 */
                        if (!(find_among_b(z, a_20, 8))) goto lab24; /* among, line 279 */
                        goto lab23;
                    lab24:
                        z->c = z->l - m14;
                    }
                    z->c = z->l - m_test13;
                }
                goto lab9;
            lab23:
                z->c = z->l - m10;
                if (!(eq_s_b(z, 9, s_91))) goto lab8; /* literal, line 280 */
            }
        lab9:
            z->bra = z->c; /* ], line 281 */
            {   int ret = slice_from_s(z, 3, s_92); /* <-, line 281 */
                if (ret < 0) return ret;
            }
            z->c = z->l - m_test9;
        }
        goto lab0;
    lab8:
        z->c = z->l - m1;
        {   int m_test15 = z->l - z->c; /* test, line 284 */
            z->ket = z->c; /* [, line 284 */
            {   int m16 = z->l - z->c; (void)m16; /* or, line 285 */
                if (!(eq_s_b(z, 9, s_93))) goto lab27; /* literal, line 285 */
                goto lab26;
            lab27:
                z->c = z->l - m16;
                if (!(eq_s_b(z, 12, s_94))) goto lab28; /* literal, line 286 */
                goto lab26;
            lab28:
                z->c = z->l - m16;
                if (!(eq_s_b(z, 12, s_95))) goto lab29; /* literal, line 287 */
                goto lab26;
            lab29:
                z->c = z->l - m16;
                if (!(eq_s_b(z, 12, s_96))) goto lab30; /* literal, line 288 */
                goto lab26;
            lab30:
                z->c = z->l - m16;
                if (!(eq_s_b(z, 12, s_97))) goto lab31; /* literal, line 289 */
                goto lab26;
            lab31:
                z->c = z->l - m16;
                if (!(eq_s_b(z, 12, s_98))) goto lab32; /* literal, line 290 */
                goto lab26;
            lab32:
                z->c = z->l - m16;
                if (!(eq_s_b(z, 6, s_99))) goto lab25; /* literal, line 291 */
                {   int m_test17 = z->l - z->c; /* test, line 291 */
                    {   int m18 = z->l - z->c; (void)m18; /* not, line 291 */
                        if (!(find_among_b(z, a_21, 8))) goto lab33; /* among, line 291 */
                        goto lab25;
                    lab33:
                        z->c = z->l - m18;
                    }
                    z->c = z->l - m_test17;
                }
            }
        lab26:
            z->bra = z->c; /* ], line 292 */
            {   int ret = slice_del(z); /* delete, line 292 */
                if (ret < 0) return ret;
            }
            z->c = z->l - m_test15;
        }
        goto lab0;
    lab25:
        z->c = z->l - m1;
        {   int m_test19 = z->l - z->c; /* test, line 295 */
            z->ket = z->c; /* [, line 295 */
            if (!(eq_s_b(z, 3, s_100))) return 0; /* literal, line 295 */
            z->bra = z->c; /* ], line 295 */
            {   int ret = slice_from_s(z, 3, s_101); /* <-, line 295 */
                if (ret < 0) return ret;
            }
            z->c = z->l - m_test19;
        }
    }
lab0:
    z->B[0] = 1; /* set found_a_match, line 297 */
    z->B[1] = 1; /* set found_vetrumai_urupu, line 298 */
    {   int m20 = z->l - z->c; (void)m20; /* do, line 299 */
        z->ket = z->c; /* [, line 299 */
        if (!(eq_s_b(z, 9, s_102))) goto lab34; /* literal, line 299 */
        z->bra = z->c; /* ], line 299 */
        {   int ret = slice_from_s(z, 3, s_103); /* <-, line 299 */
            if (ret < 0) return ret;
        }
    lab34:
        z->c = z->l - m20;
    }
    z->c = z->lb;
    /* do, line 301 */
    {   int ret = r_fix_endings(z); /* call fix_endings, line 301 */
        if (ret == 0) goto lab35;
        if (ret < 0) return ret;
    }
lab35:
    return 1;
}