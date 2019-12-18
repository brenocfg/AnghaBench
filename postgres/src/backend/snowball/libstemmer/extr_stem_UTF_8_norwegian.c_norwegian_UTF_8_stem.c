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
 int r_consonant_pair (struct SN_env*) ; 
 int r_main_suffix (struct SN_env*) ; 
 int r_mark_regions (struct SN_env*) ; 
 int r_other_suffix (struct SN_env*) ; 

extern int norwegian_UTF_8_stem(struct SN_env * z) { /* forwardmode */
    {   int c1 = z->c; /* do, line 74 */
        {   int ret = r_mark_regions(z); /* call mark_regions, line 74 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
    lab0:
        z->c = c1;
    }
    z->lb = z->c; z->c = z->l; /* backwards, line 75 */

    {   int m2 = z->l - z->c; (void)m2; /* do, line 76 */
        {   int ret = r_main_suffix(z); /* call main_suffix, line 76 */
            if (ret == 0) goto lab1;
            if (ret < 0) return ret;
        }
    lab1:
        z->c = z->l - m2;
    }
    {   int m3 = z->l - z->c; (void)m3; /* do, line 77 */
        {   int ret = r_consonant_pair(z); /* call consonant_pair, line 77 */
            if (ret == 0) goto lab2;
            if (ret < 0) return ret;
        }
    lab2:
        z->c = z->l - m3;
    }
    {   int m4 = z->l - z->c; (void)m4; /* do, line 78 */
        {   int ret = r_other_suffix(z); /* call other_suffix, line 78 */
            if (ret == 0) goto lab3;
            if (ret < 0) return ret;
        }
    lab3:
        z->c = z->l - m4;
    }
    z->c = z->lb;
    return 1;
}