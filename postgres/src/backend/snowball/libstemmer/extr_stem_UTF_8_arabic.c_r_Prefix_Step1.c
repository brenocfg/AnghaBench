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
struct SN_env {int bra; int c; int l; int* p; int ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_4 ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int len_utf8 (int*) ; 
 int /*<<< orphan*/  s_54 ; 
 int /*<<< orphan*/  s_55 ; 
 int /*<<< orphan*/  s_56 ; 
 int /*<<< orphan*/  s_57 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Prefix_Step1(struct SN_env * z) { /* forwardmode */
    int among_var;
    z->bra = z->c; /* [, line 354 */
    if (z->c + 3 >= z->l || z->p[z->c + 3] >> 5 != 5 || !((188 >> (z->p[z->c + 3] & 0x1f)) & 1)) return 0; /* substring, line 354 */
    among_var = find_among(z, a_4, 5);
    if (!(among_var)) return 0;
    z->ket = z->c; /* ], line 354 */
    switch (among_var) { /* among, line 354 */
        case 1:
            if (!(len_utf8(z->p) > 3)) return 0; /* $(<integer expression> > <integer expression>), line 355 */
            {   int ret = slice_from_s(z, 2, s_54); /* <-, line 355 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            if (!(len_utf8(z->p) > 3)) return 0; /* $(<integer expression> > <integer expression>), line 356 */
            {   int ret = slice_from_s(z, 2, s_55); /* <-, line 356 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            if (!(len_utf8(z->p) > 3)) return 0; /* $(<integer expression> > <integer expression>), line 358 */
            {   int ret = slice_from_s(z, 2, s_56); /* <-, line 358 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            if (!(len_utf8(z->p) > 3)) return 0; /* $(<integer expression> > <integer expression>), line 359 */
            {   int ret = slice_from_s(z, 2, s_57); /* <-, line 359 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}