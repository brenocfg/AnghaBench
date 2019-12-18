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
struct SN_env {int* I; int l; int c; char* p; int lb; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_v ; 
 int in_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int len_utf8 (char*) ; 
 int out_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int r_fix_chdz (struct SN_env*) ; 
 int r_fix_conflicts (struct SN_env*) ; 
 int r_fix_gd (struct SN_env*) ; 
 int r_step1 (struct SN_env*) ; 
 int r_step2 (struct SN_env*) ; 
 int skip_utf8 (char*,int,int /*<<< orphan*/ ,int,int) ; 

extern int lithuanian_UTF_8_stem(struct SN_env * z) { /* forwardmode */
    z->I[0] = z->l; /* $p1 = <integer expression>, line 355 */
    {   int c1 = z->c; /* do, line 357 */
        {   int c2 = z->c; /* try, line 359 */
            {   int c_test3 = z->c; /* test, line 359 */
                if (z->c == z->l || z->p[z->c] != 'a') { z->c = c2; goto lab1; } /* literal, line 359 */
                z->c++;
                z->c = c_test3;
            }
            if (!(len_utf8(z->p) > 6)) { z->c = c2; goto lab1; } /* $(<integer expression> > <integer expression>), line 359 */
            {   int ret = skip_utf8(z->p, z->c, 0, z->l, + 1); /* hop, line 359 */
                if (ret < 0) { z->c = c2; goto lab1; }
                z->c = ret;
            }
        lab1:
            ;
        }
        {    /* gopast */ /* grouping v, line 361 */
            int ret = out_grouping_U(z, g_v, 97, 371, 1);
            if (ret < 0) goto lab0;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 361 */
            int ret = in_grouping_U(z, g_v, 97, 371, 1);
            if (ret < 0) goto lab0;
            z->c += ret;
        }
        z->I[0] = z->c; /* setmark p1, line 361 */
    lab0:
        z->c = c1;
    }
    z->lb = z->c; z->c = z->l; /* backwards, line 364 */

    {   int m4 = z->l - z->c; (void)m4; /* do, line 365 */
        {   int ret = r_fix_conflicts(z); /* call fix_conflicts, line 365 */
            if (ret == 0) goto lab2;
            if (ret < 0) return ret;
        }
    lab2:
        z->c = z->l - m4;
    }
    {   int m5 = z->l - z->c; (void)m5; /* do, line 366 */
        {   int ret = r_step1(z); /* call step1, line 366 */
            if (ret == 0) goto lab3;
            if (ret < 0) return ret;
        }
    lab3:
        z->c = z->l - m5;
    }
    {   int m6 = z->l - z->c; (void)m6; /* do, line 367 */
        {   int ret = r_fix_chdz(z); /* call fix_chdz, line 367 */
            if (ret == 0) goto lab4;
            if (ret < 0) return ret;
        }
    lab4:
        z->c = z->l - m6;
    }
    {   int m7 = z->l - z->c; (void)m7; /* do, line 368 */
        {   int ret = r_step2(z); /* call step2, line 368 */
            if (ret == 0) goto lab5;
            if (ret < 0) return ret;
        }
    lab5:
        z->c = z->l - m7;
    }
    {   int m8 = z->l - z->c; (void)m8; /* do, line 369 */
        {   int ret = r_fix_chdz(z); /* call fix_chdz, line 369 */
            if (ret == 0) goto lab6;
            if (ret < 0) return ret;
        }
    lab6:
        z->c = z->l - m8;
    }
    {   int m9 = z->l - z->c; (void)m9; /* do, line 370 */
        {   int ret = r_fix_gd(z); /* call fix_gd, line 370 */
            if (ret == 0) goto lab7;
            if (ret < 0) return ret;
        }
    lab7:
        z->c = z->l - m9;
    }
    z->c = z->lb;
    return 1;
}