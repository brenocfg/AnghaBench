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
 int r_deriv (struct SN_env*) ; 
 int r_initial_morph (struct SN_env*) ; 
 int r_mark_regions (struct SN_env*) ; 
 int r_noun_sfx (struct SN_env*) ; 
 int r_verb_sfx (struct SN_env*) ; 

extern int irish_UTF_8_stem(struct SN_env * z) { /* forwardmode */
    {   int c1 = z->c; /* do, line 144 */
        {   int ret = r_initial_morph(z); /* call initial_morph, line 144 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
    lab0:
        z->c = c1;
    }
    /* do, line 145 */
    {   int ret = r_mark_regions(z); /* call mark_regions, line 145 */
        if (ret == 0) goto lab1;
        if (ret < 0) return ret;
    }
lab1:
    z->lb = z->c; z->c = z->l; /* backwards, line 146 */

    {   int m2 = z->l - z->c; (void)m2; /* do, line 147 */
        {   int ret = r_noun_sfx(z); /* call noun_sfx, line 147 */
            if (ret == 0) goto lab2;
            if (ret < 0) return ret;
        }
    lab2:
        z->c = z->l - m2;
    }
    {   int m3 = z->l - z->c; (void)m3; /* do, line 148 */
        {   int ret = r_deriv(z); /* call deriv, line 148 */
            if (ret == 0) goto lab3;
            if (ret < 0) return ret;
        }
    lab3:
        z->c = z->l - m3;
    }
    {   int m4 = z->l - z->c; (void)m4; /* do, line 149 */
        {   int ret = r_verb_sfx(z); /* call verb_sfx, line 149 */
            if (ret == 0) goto lab4;
            if (ret < 0) return ret;
        }
    lab4:
        z->c = z->l - m4;
    }
    z->c = z->lb;
    return 1;
}