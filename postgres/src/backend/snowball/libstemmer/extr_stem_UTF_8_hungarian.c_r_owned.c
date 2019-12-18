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
 int /*<<< orphan*/  a_9 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int /*<<< orphan*/  s_8 ; 
 int /*<<< orphan*/  s_9 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_owned(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 154 */
    if (z->c - 1 <= z->lb || (z->p[z->c - 1] != 105 && z->p[z->c - 1] != 169)) return 0; /* substring, line 154 */
    among_var = find_among_b(z, a_9, 12);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 154 */
    {   int ret = r_R1(z); /* call R1, line 154 */
        if (ret <= 0) return ret;
    }
    switch (among_var) { /* among, line 154 */
        case 1:
            {   int ret = slice_del(z); /* delete, line 155 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 1, s_8); /* <-, line 156 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 1, s_9); /* <-, line 157 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}