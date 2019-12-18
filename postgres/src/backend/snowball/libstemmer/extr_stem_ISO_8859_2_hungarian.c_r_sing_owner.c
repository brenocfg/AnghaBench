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
struct SN_env {int /*<<< orphan*/  c; int /*<<< orphan*/  bra; int /*<<< orphan*/  ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_10 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int r_R1 (struct SN_env*) ; 
 int /*<<< orphan*/  s_10 ; 
 int /*<<< orphan*/  s_11 ; 
 int slice_del (struct SN_env*) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_sing_owner(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 168 */
    among_var = find_among_b(z, a_10, 31); /* substring, line 168 */
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 168 */
    {   int ret = r_R1(z); /* call R1, line 168 */
        if (ret <= 0) return ret;
    }
    switch (among_var) { /* among, line 168 */
        case 1:
            {   int ret = slice_del(z); /* delete, line 169 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 1, s_10); /* <-, line 170 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 1, s_11); /* <-, line 171 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}