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
struct SN_env {int c; int lb; int l; } ;

/* Variables and functions */
 int r_case (struct SN_env*) ; 
 int r_case_other (struct SN_env*) ; 
 int r_case_special (struct SN_env*) ; 
 int r_factive (struct SN_env*) ; 
 int r_instrum (struct SN_env*) ; 
 int r_mark_regions (struct SN_env*) ; 
 int r_owned (struct SN_env*) ; 
 int r_plur_owner (struct SN_env*) ; 
 int r_plural (struct SN_env*) ; 
 int r_sing_owner (struct SN_env*) ; 

extern int hungarian_ISO_8859_2_stem(struct SN_env * z) { /* forwardmode */
    {   int c1 = z->c; /* do, line 229 */
        {   int ret = r_mark_regions(z); /* call mark_regions, line 229 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
    lab0:
        z->c = c1;
    }
    z->lb = z->c; z->c = z->l; /* backwards, line 230 */

    {   int m2 = z->l - z->c; (void)m2; /* do, line 231 */
        {   int ret = r_instrum(z); /* call instrum, line 231 */
            if (ret == 0) goto lab1;
            if (ret < 0) return ret;
        }
    lab1:
        z->c = z->l - m2;
    }
    {   int m3 = z->l - z->c; (void)m3; /* do, line 232 */
        {   int ret = r_case(z); /* call case, line 232 */
            if (ret == 0) goto lab2;
            if (ret < 0) return ret;
        }
    lab2:
        z->c = z->l - m3;
    }
    {   int m4 = z->l - z->c; (void)m4; /* do, line 233 */
        {   int ret = r_case_special(z); /* call case_special, line 233 */
            if (ret == 0) goto lab3;
            if (ret < 0) return ret;
        }
    lab3:
        z->c = z->l - m4;
    }
    {   int m5 = z->l - z->c; (void)m5; /* do, line 234 */
        {   int ret = r_case_other(z); /* call case_other, line 234 */
            if (ret == 0) goto lab4;
            if (ret < 0) return ret;
        }
    lab4:
        z->c = z->l - m5;
    }
    {   int m6 = z->l - z->c; (void)m6; /* do, line 235 */
        {   int ret = r_factive(z); /* call factive, line 235 */
            if (ret == 0) goto lab5;
            if (ret < 0) return ret;
        }
    lab5:
        z->c = z->l - m6;
    }
    {   int m7 = z->l - z->c; (void)m7; /* do, line 236 */
        {   int ret = r_owned(z); /* call owned, line 236 */
            if (ret == 0) goto lab6;
            if (ret < 0) return ret;
        }
    lab6:
        z->c = z->l - m7;
    }
    {   int m8 = z->l - z->c; (void)m8; /* do, line 237 */
        {   int ret = r_sing_owner(z); /* call sing_owner, line 237 */
            if (ret == 0) goto lab7;
            if (ret < 0) return ret;
        }
    lab7:
        z->c = z->l - m8;
    }
    {   int m9 = z->l - z->c; (void)m9; /* do, line 238 */
        {   int ret = r_plur_owner(z); /* call plur_owner, line 238 */
            if (ret == 0) goto lab8;
            if (ret < 0) return ret;
        }
    lab8:
        z->c = z->l - m9;
    }
    {   int m10 = z->l - z->c; (void)m10; /* do, line 239 */
        {   int ret = r_plural(z); /* call plural, line 239 */
            if (ret == 0) goto lab9;
            if (ret < 0) return ret;
        }
    lab9:
        z->c = z->l - m10;
    }
    z->c = z->lb;
    return 1;
}