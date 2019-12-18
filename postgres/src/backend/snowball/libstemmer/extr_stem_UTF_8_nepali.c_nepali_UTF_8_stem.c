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
 int r_check_category_2 (struct SN_env*) ; 
 int r_remove_category_1 (struct SN_env*) ; 
 int r_remove_category_2 (struct SN_env*) ; 
 int r_remove_category_3 (struct SN_env*) ; 

extern int nepali_UTF_8_stem(struct SN_env * z) { /* forwardmode */
    z->lb = z->c; z->c = z->l; /* backwards, line 86 */

    {   int m1 = z->l - z->c; (void)m1; /* do, line 87 */
        {   int ret = r_remove_category_1(z); /* call remove_category_1, line 87 */
            if (ret == 0) goto lab0;
            if (ret < 0) return ret;
        }
    lab0:
        z->c = z->l - m1;
    }
    {   int m2 = z->l - z->c; (void)m2; /* do, line 88 */
        while(1) { /* repeat, line 89 */
            int m3 = z->l - z->c; (void)m3;
            {   int m4 = z->l - z->c; (void)m4; /* do, line 89 */
                {   int m5 = z->l - z->c; (void)m5; /* and, line 89 */
                    {   int ret = r_check_category_2(z); /* call check_category_2, line 89 */
                        if (ret == 0) goto lab3;
                        if (ret < 0) return ret;
                    }
                    z->c = z->l - m5;
                    {   int ret = r_remove_category_2(z); /* call remove_category_2, line 89 */
                        if (ret == 0) goto lab3;
                        if (ret < 0) return ret;
                    }
                }
            lab3:
                z->c = z->l - m4;
            }
            {   int ret = r_remove_category_3(z); /* call remove_category_3, line 89 */
                if (ret == 0) goto lab2;
                if (ret < 0) return ret;
            }
            continue;
        lab2:
            z->c = z->l - m3;
            break;
        }
        z->c = z->l - m2;
    }
    z->c = z->lb;
    return 1;
}