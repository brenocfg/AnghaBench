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
struct SN_env {int l; int c; int lb; char* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  eq_s_b (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_vowel ; 
 int insert_s (struct SN_env*,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ out_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  s_10 ; 
 int /*<<< orphan*/  s_11 ; 
 int /*<<< orphan*/  s_12 ; 
 int /*<<< orphan*/  s_13 ; 
 int /*<<< orphan*/  s_14 ; 
 int /*<<< orphan*/  s_15 ; 
 int /*<<< orphan*/  s_9 ; 

__attribute__((used)) static int r_append_U_to_stems_ending_with_d_or_g(struct SN_env * z) { /* backwardmode */
    {   int m_test1 = z->l - z->c; /* test, line 429 */
        {   int m2 = z->l - z->c; (void)m2; /* or, line 429 */
            if (z->c <= z->lb || z->p[z->c - 1] != 'd') goto lab1; /* literal, line 429 */
            z->c--;
            goto lab0;
        lab1:
            z->c = z->l - m2;
            if (z->c <= z->lb || z->p[z->c - 1] != 'g') return 0; /* literal, line 429 */
            z->c--;
        }
    lab0:
        z->c = z->l - m_test1;
    }
    {   int m3 = z->l - z->c; (void)m3; /* or, line 431 */
        {   int m_test4 = z->l - z->c; /* test, line 430 */
            if (out_grouping_b_U(z, g_vowel, 97, 305, 1) < 0) goto lab3; /* goto */ /* grouping vowel, line 430 */
            {   int m5 = z->l - z->c; (void)m5; /* or, line 430 */
                if (z->c <= z->lb || z->p[z->c - 1] != 'a') goto lab5; /* literal, line 430 */
                z->c--;
                goto lab4;
            lab5:
                z->c = z->l - m5;
                if (!(eq_s_b(z, 2, s_9))) goto lab3; /* literal, line 430 */
            }
        lab4:
            z->c = z->l - m_test4;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_s(z, z->c, z->c, 2, s_10); /* <+, line 430 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab2;
    lab3:
        z->c = z->l - m3;
        {   int m_test6 = z->l - z->c; /* test, line 432 */
            if (out_grouping_b_U(z, g_vowel, 97, 305, 1) < 0) goto lab6; /* goto */ /* grouping vowel, line 432 */
            {   int m7 = z->l - z->c; (void)m7; /* or, line 432 */
                if (z->c <= z->lb || z->p[z->c - 1] != 'e') goto lab8; /* literal, line 432 */
                z->c--;
                goto lab7;
            lab8:
                z->c = z->l - m7;
                if (z->c <= z->lb || z->p[z->c - 1] != 'i') goto lab6; /* literal, line 432 */
                z->c--;
            }
        lab7:
            z->c = z->l - m_test6;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_s(z, z->c, z->c, 1, s_11); /* <+, line 432 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab2;
    lab6:
        z->c = z->l - m3;
        {   int m_test8 = z->l - z->c; /* test, line 434 */
            if (out_grouping_b_U(z, g_vowel, 97, 305, 1) < 0) goto lab9; /* goto */ /* grouping vowel, line 434 */
            {   int m9 = z->l - z->c; (void)m9; /* or, line 434 */
                if (z->c <= z->lb || z->p[z->c - 1] != 'o') goto lab11; /* literal, line 434 */
                z->c--;
                goto lab10;
            lab11:
                z->c = z->l - m9;
                if (z->c <= z->lb || z->p[z->c - 1] != 'u') goto lab9; /* literal, line 434 */
                z->c--;
            }
        lab10:
            z->c = z->l - m_test8;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_s(z, z->c, z->c, 1, s_12); /* <+, line 434 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab2;
    lab9:
        z->c = z->l - m3;
        {   int m_test10 = z->l - z->c; /* test, line 436 */
            if (out_grouping_b_U(z, g_vowel, 97, 305, 1) < 0) return 0; /* goto */ /* grouping vowel, line 436 */
            {   int m11 = z->l - z->c; (void)m11; /* or, line 436 */
                if (!(eq_s_b(z, 2, s_13))) goto lab13; /* literal, line 436 */
                goto lab12;
            lab13:
                z->c = z->l - m11;
                if (!(eq_s_b(z, 2, s_14))) return 0; /* literal, line 436 */
            }
        lab12:
            z->c = z->l - m_test10;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_s(z, z->c, z->c, 2, s_15); /* <+, line 436 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
    }
lab2:
    return 1;
}