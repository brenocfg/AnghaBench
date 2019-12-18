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
struct SN_env {int ket; int c; int bra; int l; int lb; int* p; scalar_t__* S; scalar_t__* B; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_2 ; 
 int /*<<< orphan*/  a_3 ; 
 int /*<<< orphan*/  a_4 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int insert_v (struct SN_env*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  s_35 ; 
 int /*<<< orphan*/  s_36 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 void* slice_to (struct SN_env*,scalar_t__) ; 

__attribute__((used)) static int r_steps1(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 185 */
    if (!(find_among_b(z, a_4, 14))) return 0; /* substring, line 185 */
    z->bra = z->c; /* ], line 185 */
    {   int ret = slice_del(z); /* delete, line 188 */
        if (ret < 0) return ret;
    }
    z->B[0] = 0; /* unset test1, line 189 */
    {   int m1 = z->l - z->c; (void)m1; /* or, line 193 */
        z->ket = z->c; /* [, line 190 */
        if (z->c - 3 <= z->lb || z->p[z->c - 1] >> 5 != 5 || !((-2145255424 >> (z->p[z->c - 1] & 0x1f)) & 1)) goto lab1; /* substring, line 190 */
        if (!(find_among_b(z, a_2, 9))) goto lab1;
        z->bra = z->c; /* ], line 190 */
        if (z->c > z->lb) goto lab1; /* atlimit, line 190 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 192 */
        if (z->S[0] == 0) return -1; /* -> s, line 192 */
        {   int ret = slice_from_s(z, 2, s_35); /* <-, line 192 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 192 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        z->ket = z->c; /* [, line 194 */
        if (!(find_among_b(z, a_3, 22))) return 0; /* substring, line 194 */
        z->bra = z->c; /* ], line 194 */
        if (z->c > z->lb) return 0; /* atlimit, line 194 */
        z->S[0] = slice_to(z, z->S[0]); /* -> s, line 198 */
        if (z->S[0] == 0) return -1; /* -> s, line 198 */
        {   int ret = slice_from_s(z, 4, s_36); /* <-, line 198 */
            if (ret < 0) return ret;
        }
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ s, line 198 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
    }
lab0:
    return 1;
}