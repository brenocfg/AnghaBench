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
struct SN_env {int* B; int lb; int c; int l; int ket; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_16 ; 
 int /*<<< orphan*/  a_17 ; 
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_fix_endings (struct SN_env*) ; 
 int r_has_min_length (struct SN_env*) ; 
 int /*<<< orphan*/  s_56 ; 
 int /*<<< orphan*/  s_57 ; 
 int /*<<< orphan*/  s_58 ; 
 int /*<<< orphan*/  s_59 ; 
 int /*<<< orphan*/  s_60 ; 
 int /*<<< orphan*/  s_61 ; 
 int /*<<< orphan*/  s_62 ; 
 int /*<<< orphan*/  s_63 ; 
 int /*<<< orphan*/  s_64 ; 
 int /*<<< orphan*/  s_65 ; 
 int /*<<< orphan*/  s_66 ; 
 int /*<<< orphan*/  s_67 ; 
 int /*<<< orphan*/  s_68 ; 
 int /*<<< orphan*/  s_69 ; 
 int /*<<< orphan*/  s_70 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_remove_common_word_endings(struct SN_env * z) { /* forwardmode */
    z->B[0] = 0; /* unset found_a_match, line 212 */
    {   int ret = r_has_min_length(z); /* call has_min_length, line 213 */
        if (ret <= 0) return ret;
    }
    z->lb = z->c; z->c = z->l; /* backwards, line 214 */

    {   int m1 = z->l - z->c; (void)m1; /* or, line 231 */
        {   int m_test2 = z->l - z->c; /* test, line 215 */
            z->ket = z->c; /* [, line 215 */
            {   int m3 = z->l - z->c; (void)m3; /* or, line 215 */
                if (!(eq_s_b(z, 12, s_56))) goto lab3; /* literal, line 215 */
                goto lab2;
            lab3:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 15, s_57))) goto lab4; /* literal, line 216 */
                goto lab2;
            lab4:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 12, s_58))) goto lab5; /* literal, line 217 */
                goto lab2;
            lab5:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 15, s_59))) goto lab6; /* literal, line 218 */
                goto lab2;
            lab6:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 9, s_60))) goto lab7; /* literal, line 219 */
                goto lab2;
            lab7:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 12, s_61))) goto lab8; /* literal, line 220 */
                goto lab2;
            lab8:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 15, s_62))) goto lab9; /* literal, line 221 */
                goto lab2;
            lab9:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 12, s_63))) goto lab10; /* literal, line 222 */
                goto lab2;
            lab10:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 12, s_64))) goto lab11; /* literal, line 223 */
                goto lab2;
            lab11:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 9, s_65))) goto lab12; /* literal, line 224 */
                goto lab2;
            lab12:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 15, s_66))) goto lab13; /* literal, line 225 */
                goto lab2;
            lab13:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 9, s_67))) goto lab14; /* literal, line 226 */
                {   int m_test4 = z->l - z->c; /* test, line 226 */
                    {   int m5 = z->l - z->c; (void)m5; /* not, line 226 */
                        if (!(find_among_b(z, a_16, 8))) goto lab15; /* among, line 226 */
                        goto lab14;
                    lab15:
                        z->c = z->l - m5;
                    }
                    z->c = z->l - m_test4;
                }
                goto lab2;
            lab14:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 6, s_68))) goto lab16; /* literal, line 227 */
                goto lab2;
            lab16:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 9, s_69))) goto lab1; /* literal, line 228 */
            }
        lab2:
            z->bra = z->c; /* ], line 228 */
            {   int ret = slice_from_s(z, 3, s_70); /* <-, line 228 */
                if (ret < 0) return ret;
            }
            z->B[0] = 1; /* set found_a_match, line 229 */
            z->c = z->l - m_test2;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        {   int m_test6 = z->l - z->c; /* test, line 232 */
            z->ket = z->c; /* [, line 232 */
            if (!(find_among_b(z, a_17, 13))) return 0; /* among, line 232 */
            z->bra = z->c; /* ], line 245 */
            {   int ret = slice_del(z); /* delete, line 245 */
                if (ret < 0) return ret;
            }
            z->B[0] = 1; /* set found_a_match, line 246 */
            z->c = z->l - m_test6;
        }
    }
lab0:
    z->c = z->lb;
    /* do, line 249 */
    {   int ret = r_fix_endings(z); /* call fix_endings, line 249 */
        if (ret == 0) goto lab17;
        if (ret < 0) return ret;
    }
lab17:
    return 1;
}