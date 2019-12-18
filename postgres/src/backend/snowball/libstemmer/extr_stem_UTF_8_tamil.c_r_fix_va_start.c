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
struct SN_env {int c; int bra; int ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  eq_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_0 ; 
 int /*<<< orphan*/  s_1 ; 
 int /*<<< orphan*/  s_10 ; 
 int /*<<< orphan*/  s_11 ; 
 int /*<<< orphan*/  s_2 ; 
 int /*<<< orphan*/  s_3 ; 
 int /*<<< orphan*/  s_4 ; 
 int /*<<< orphan*/  s_5 ; 
 int /*<<< orphan*/  s_6 ; 
 int /*<<< orphan*/  s_7 ; 
 int /*<<< orphan*/  s_8 ; 
 int /*<<< orphan*/  s_9 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_fix_va_start(struct SN_env * z) { /* forwardmode */
    {   int c1 = z->c; /* or, line 104 */
        {   int c2 = z->c; /* and, line 104 */
            {   int c3 = z->c; /* try, line 104 */
                if (!(eq_s(z, 6, s_0))) { z->c = c3; goto lab2; } /* literal, line 104 */
            lab2:
                ;
            }
            z->c = c2;
            z->bra = z->c; /* [, line 104 */
        }
        if (!(eq_s(z, 6, s_1))) goto lab1; /* literal, line 104 */
        z->ket = z->c; /* ], line 104 */
        {   int ret = slice_from_s(z, 3, s_2); /* <-, line 104 */
            if (ret < 0) return ret;
        }
        goto lab0;
    lab1:
        z->c = c1;
        {   int c4 = z->c; /* and, line 105 */
            {   int c5 = z->c; /* try, line 105 */
                if (!(eq_s(z, 6, s_3))) { z->c = c5; goto lab4; } /* literal, line 105 */
            lab4:
                ;
            }
            z->c = c4;
            z->bra = z->c; /* [, line 105 */
        }
        if (!(eq_s(z, 6, s_4))) goto lab3; /* literal, line 105 */
        z->ket = z->c; /* ], line 105 */
        {   int ret = slice_from_s(z, 3, s_5); /* <-, line 105 */
            if (ret < 0) return ret;
        }
        goto lab0;
    lab3:
        z->c = c1;
        {   int c6 = z->c; /* and, line 106 */
            {   int c7 = z->c; /* try, line 106 */
                if (!(eq_s(z, 6, s_6))) { z->c = c7; goto lab6; } /* literal, line 106 */
            lab6:
                ;
            }
            z->c = c6;
            z->bra = z->c; /* [, line 106 */
        }
        if (!(eq_s(z, 6, s_7))) goto lab5; /* literal, line 106 */
        z->ket = z->c; /* ], line 106 */
        {   int ret = slice_from_s(z, 3, s_8); /* <-, line 106 */
            if (ret < 0) return ret;
        }
        goto lab0;
    lab5:
        z->c = c1;
        {   int c8 = z->c; /* and, line 107 */
            {   int c9 = z->c; /* try, line 107 */
                if (!(eq_s(z, 6, s_9))) { z->c = c9; goto lab7; } /* literal, line 107 */
            lab7:
                ;
            }
            z->c = c8;
            z->bra = z->c; /* [, line 107 */
        }
        if (!(eq_s(z, 6, s_10))) return 0; /* literal, line 107 */
        z->ket = z->c; /* ], line 107 */
        {   int ret = slice_from_s(z, 3, s_11); /* <-, line 107 */
            if (ret < 0) return ret;
        }
    }
lab0:
    return 1;
}