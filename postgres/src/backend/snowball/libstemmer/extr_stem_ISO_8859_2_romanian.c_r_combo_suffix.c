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
struct SN_env {int l; int c; int ket; int bra; int* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_2 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int /*<<< orphan*/  s_11 ; 
 int /*<<< orphan*/  s_12 ; 
 int /*<<< orphan*/  s_13 ; 
 int /*<<< orphan*/  s_14 ; 
 int /*<<< orphan*/  s_15 ; 
 int /*<<< orphan*/  s_16 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_combo_suffix(struct SN_env * z) { /* backwardmode */
    int among_var;
    {   int m_test1 = z->l - z->c; /* test, line 91 */
        z->ket = z->c; /* [, line 92 */
        among_var = find_among_b(z, a_2, 46); /* substring, line 92 */
        if (!(among_var)) return 0;
        z->bra = z->c; /* ], line 92 */
        {   int ret = r_R1(z); /* call R1, line 92 */
            if (ret <= 0) return ret;
        }
        switch (among_var) { /* among, line 93 */
            case 1:
                {   int ret = slice_from_s(z, 4, s_11); /* <-, line 101 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = slice_from_s(z, 4, s_12); /* <-, line 104 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = slice_from_s(z, 2, s_13); /* <-, line 107 */
                    if (ret < 0) return ret;
                }
                break;
            case 4:
                {   int ret = slice_from_s(z, 2, s_14); /* <-, line 113 */
                    if (ret < 0) return ret;
                }
                break;
            case 5:
                {   int ret = slice_from_s(z, 2, s_15); /* <-, line 118 */
                    if (ret < 0) return ret;
                }
                break;
            case 6:
                {   int ret = slice_from_s(z, 2, s_16); /* <-, line 122 */
                    if (ret < 0) return ret;
                }
                break;
        }
        z->B[0] = 1; /* set standard_suffix_removed, line 125 */
        z->c = z->l - m_test1;
    }
    return 1;
}