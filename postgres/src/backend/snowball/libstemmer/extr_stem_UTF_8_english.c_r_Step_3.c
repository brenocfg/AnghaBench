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
struct SN_env {int ket; int c; int lb; int* p; int bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_6 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int r_R2 (struct SN_env*) ; 
 int /*<<< orphan*/  s_23 ; 
 int /*<<< orphan*/  s_24 ; 
 int /*<<< orphan*/  s_25 ; 
 int /*<<< orphan*/  s_26 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Step_3(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 127 */
    if (z->c - 2 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((528928 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* substring, line 127 */
    among_var = find_among_b(z, a_6, 9);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 127 */
    {   int ret = r_R1(z); /* call R1, line 127 */
        if (ret <= 0) return ret;
    }
    switch (among_var) { /* among, line 127 */
        case 1:
            {   int ret = slice_from_s(z, 4, s_23); /* <-, line 128 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 3, s_24); /* <-, line 129 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 2, s_25); /* <-, line 130 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = slice_from_s(z, 2, s_26); /* <-, line 132 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = slice_del(z); /* delete, line 134 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = r_R2(z); /* call R2, line 136 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 136 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}