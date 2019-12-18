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
 int /*<<< orphan*/  g_vowel1 ; 
 int /*<<< orphan*/  g_vowel2 ; 
 int /*<<< orphan*/  g_vowel3 ; 
 int /*<<< orphan*/  g_vowel4 ; 
 int /*<<< orphan*/  g_vowel5 ; 
 int /*<<< orphan*/  g_vowel6 ; 
 scalar_t__ out_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  s_0 ; 
 int /*<<< orphan*/  s_1 ; 
 int /*<<< orphan*/  s_2 ; 

__attribute__((used)) static int r_check_vowel_harmony(struct SN_env * z) { /* backwardmode */
    {   int m_test1 = z->l - z->c; /* test, line 110 */
        if (out_grouping_b_U(z, g_vowel, 97, 305, 1) < 0) return 0; /* goto */ /* grouping vowel, line 112 */
        {   int m2 = z->l - z->c; (void)m2; /* or, line 114 */
            if (z->c <= z->lb || z->p[z->c - 1] != 'a') goto lab1; /* literal, line 114 */
            z->c--;
            if (out_grouping_b_U(z, g_vowel1, 97, 305, 1) < 0) goto lab1; /* goto */ /* grouping vowel1, line 114 */
            goto lab0;
        lab1:
            z->c = z->l - m2;
            if (z->c <= z->lb || z->p[z->c - 1] != 'e') goto lab2; /* literal, line 115 */
            z->c--;
            if (out_grouping_b_U(z, g_vowel2, 101, 252, 1) < 0) goto lab2; /* goto */ /* grouping vowel2, line 115 */
            goto lab0;
        lab2:
            z->c = z->l - m2;
            if (!(eq_s_b(z, 2, s_0))) goto lab3; /* literal, line 116 */
            if (out_grouping_b_U(z, g_vowel3, 97, 305, 1) < 0) goto lab3; /* goto */ /* grouping vowel3, line 116 */
            goto lab0;
        lab3:
            z->c = z->l - m2;
            if (z->c <= z->lb || z->p[z->c - 1] != 'i') goto lab4; /* literal, line 117 */
            z->c--;
            if (out_grouping_b_U(z, g_vowel4, 101, 105, 1) < 0) goto lab4; /* goto */ /* grouping vowel4, line 117 */
            goto lab0;
        lab4:
            z->c = z->l - m2;
            if (z->c <= z->lb || z->p[z->c - 1] != 'o') goto lab5; /* literal, line 118 */
            z->c--;
            if (out_grouping_b_U(z, g_vowel5, 111, 117, 1) < 0) goto lab5; /* goto */ /* grouping vowel5, line 118 */
            goto lab0;
        lab5:
            z->c = z->l - m2;
            if (!(eq_s_b(z, 2, s_1))) goto lab6; /* literal, line 119 */
            if (out_grouping_b_U(z, g_vowel6, 246, 252, 1) < 0) goto lab6; /* goto */ /* grouping vowel6, line 119 */
            goto lab0;
        lab6:
            z->c = z->l - m2;
            if (z->c <= z->lb || z->p[z->c - 1] != 'u') goto lab7; /* literal, line 120 */
            z->c--;
            if (out_grouping_b_U(z, g_vowel5, 111, 117, 1) < 0) goto lab7; /* goto */ /* grouping vowel5, line 120 */
            goto lab0;
        lab7:
            z->c = z->l - m2;
            if (!(eq_s_b(z, 2, s_2))) return 0; /* literal, line 121 */
            if (out_grouping_b_U(z, g_vowel6, 246, 252, 1) < 0) return 0; /* goto */ /* grouping vowel6, line 121 */
        }
    lab0:
        z->c = z->l - m_test1;
    }
    return 1;
}