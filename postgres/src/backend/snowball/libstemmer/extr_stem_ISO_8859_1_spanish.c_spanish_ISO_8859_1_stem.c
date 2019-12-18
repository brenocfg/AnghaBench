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
struct SN_env {int lb; int c; int l; } ;

/* Variables and functions */
 int r_attached_pronoun (struct SN_env*) ; 
 int r_mark_regions (struct SN_env*) ; 
 int r_postlude (struct SN_env*) ; 
 int r_residual_suffix (struct SN_env*) ; 
 int r_standard_suffix (struct SN_env*) ; 
 int r_verb_suffix (struct SN_env*) ; 
 int r_y_verb_suffix (struct SN_env*) ; 

extern int spanish_ISO_8859_1_stem(struct SN_env * z) { /* forwardmode */
    /* do, line 216 */
    {   int ret = r_mark_regions(z); /* call mark_regions, line 216 */
        if (ret == 0) goto lab0;
        if (ret < 0) return ret;
    }
lab0:
    z->lb = z->c; z->c = z->l; /* backwards, line 217 */

    {   int m1 = z->l - z->c; (void)m1; /* do, line 218 */
        {   int ret = r_attached_pronoun(z); /* call attached_pronoun, line 218 */
            if (ret == 0) goto lab1;
            if (ret < 0) return ret;
        }
    lab1:
        z->c = z->l - m1;
    }
    {   int m2 = z->l - z->c; (void)m2; /* do, line 219 */
        {   int m3 = z->l - z->c; (void)m3; /* or, line 219 */
            {   int ret = r_standard_suffix(z); /* call standard_suffix, line 219 */
                if (ret == 0) goto lab4;
                if (ret < 0) return ret;
            }
            goto lab3;
        lab4:
            z->c = z->l - m3;
            {   int ret = r_y_verb_suffix(z); /* call y_verb_suffix, line 220 */
                if (ret == 0) goto lab5;
                if (ret < 0) return ret;
            }
            goto lab3;
        lab5:
            z->c = z->l - m3;
            {   int ret = r_verb_suffix(z); /* call verb_suffix, line 221 */
                if (ret == 0) goto lab2;
                if (ret < 0) return ret;
            }
        }
    lab3:
    lab2:
        z->c = z->l - m2;
    }
    {   int m4 = z->l - z->c; (void)m4; /* do, line 223 */
        {   int ret = r_residual_suffix(z); /* call residual_suffix, line 223 */
            if (ret == 0) goto lab6;
            if (ret < 0) return ret;
        }
    lab6:
        z->c = z->l - m4;
    }
    z->c = z->lb;
    {   int c5 = z->c; /* do, line 225 */
        {   int ret = r_postlude(z); /* call postlude, line 225 */
            if (ret == 0) goto lab7;
            if (ret < 0) return ret;
        }
    lab7:
        z->c = c5;
    }
    return 1;
}