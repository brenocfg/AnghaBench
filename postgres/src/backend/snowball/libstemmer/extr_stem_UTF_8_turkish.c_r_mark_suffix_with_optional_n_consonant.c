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
 int /*<<< orphan*/  g_vowel ; 
 scalar_t__ in_grouping_b_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int skip_utf8 (char*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r_mark_suffix_with_optional_n_consonant(struct SN_env * z) { /* backwardmode */
    {   int m1 = z->l - z->c; (void)m1; /* or, line 132 */
        if (z->c <= z->lb || z->p[z->c - 1] != 'n') goto lab1; /* literal, line 131 */
        z->c--;
        {   int m_test2 = z->l - z->c; /* test, line 131 */
            if (in_grouping_b_U(z, g_vowel, 97, 305, 0)) goto lab1; /* grouping vowel, line 131 */
            z->c = z->l - m_test2;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        {   int m3 = z->l - z->c; (void)m3; /* not, line 133 */
            {   int m_test4 = z->l - z->c; /* test, line 133 */
                if (z->c <= z->lb || z->p[z->c - 1] != 'n') goto lab2; /* literal, line 133 */
                z->c--;
                z->c = z->l - m_test4;
            }
            return 0;
        lab2:
            z->c = z->l - m3;
        }
        {   int m_test5 = z->l - z->c; /* test, line 133 */
            {   int ret = skip_utf8(z->p, z->c, z->lb, 0, -1);
                if (ret < 0) return 0;
                z->c = ret; /* next, line 133 */
            }
            if (in_grouping_b_U(z, g_vowel, 97, 305, 0)) return 0; /* grouping vowel, line 133 */
            z->c = z->l - m_test5;
        }
    }
lab0:
    return 1;
}