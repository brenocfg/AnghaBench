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
struct SN_env {int* I; int c; int lb; int l; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_vowel ; 
 int out_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int r_remove_first_order_prefix (struct SN_env*) ; 
 int r_remove_particle (struct SN_env*) ; 
 int r_remove_possessive_pronoun (struct SN_env*) ; 
 int r_remove_second_order_prefix (struct SN_env*) ; 
 int r_remove_suffix (struct SN_env*) ; 

extern int indonesian_ISO_8859_1_stem(struct SN_env * z) { /* forwardmode */
    z->I[0] = 0; /* $measure = <integer expression>, line 172 */
    {   int c1 = z->c; /* do, line 173 */
        while(1) { /* repeat, line 173 */
            int c2 = z->c;
            {    /* gopast */ /* grouping vowel, line 173 */
                int ret = out_grouping(z, g_vowel, 97, 117, 1);
                if (ret < 0) goto lab1;
                z->c += ret;
            }
            z->I[0] += 1; /* $measure += <integer expression>, line 173 */
            continue;
        lab1:
            z->c = c2;
            break;
        }
        z->c = c1;
    }
    if (!(z->I[0] > 2)) return 0; /* $(<integer expression> > <integer expression>), line 174 */
    z->I[1] = 0; /* $prefix = <integer expression>, line 175 */
    z->lb = z->c; z->c = z->l; /* backwards, line 176 */

    {   int m3 = z->l - z->c; (void)m3; /* do, line 177 */
        {   int ret = r_remove_particle(z); /* call remove_particle, line 177 */
            if (ret == 0) goto lab2;
            if (ret < 0) return ret;
        }
    lab2:
        z->c = z->l - m3;
    }
    if (!(z->I[0] > 2)) return 0; /* $(<integer expression> > <integer expression>), line 178 */
    {   int m4 = z->l - z->c; (void)m4; /* do, line 179 */
        {   int ret = r_remove_possessive_pronoun(z); /* call remove_possessive_pronoun, line 179 */
            if (ret == 0) goto lab3;
            if (ret < 0) return ret;
        }
    lab3:
        z->c = z->l - m4;
    }
    z->c = z->lb;
    if (!(z->I[0] > 2)) return 0; /* $(<integer expression> > <integer expression>), line 181 */
    {   int c5 = z->c; /* or, line 188 */
        {   int c_test6 = z->c; /* test, line 182 */
            {   int ret = r_remove_first_order_prefix(z); /* call remove_first_order_prefix, line 183 */
                if (ret == 0) goto lab5;
                if (ret < 0) return ret;
            }
            {   int c7 = z->c; /* do, line 184 */
                {   int c_test8 = z->c; /* test, line 185 */
                    if (!(z->I[0] > 2)) goto lab6; /* $(<integer expression> > <integer expression>), line 185 */
                    z->lb = z->c; z->c = z->l; /* backwards, line 185 */

                    {   int ret = r_remove_suffix(z); /* call remove_suffix, line 185 */
                        if (ret == 0) goto lab6;
                        if (ret < 0) return ret;
                    }
                    z->c = z->lb;
                    z->c = c_test8;
                }
                if (!(z->I[0] > 2)) goto lab6; /* $(<integer expression> > <integer expression>), line 186 */
                {   int ret = r_remove_second_order_prefix(z); /* call remove_second_order_prefix, line 186 */
                    if (ret == 0) goto lab6;
                    if (ret < 0) return ret;
                }
            lab6:
                z->c = c7;
            }
            z->c = c_test6;
        }
        goto lab4;
    lab5:
        z->c = c5;
        {   int c9 = z->c; /* do, line 189 */
            {   int ret = r_remove_second_order_prefix(z); /* call remove_second_order_prefix, line 189 */
                if (ret == 0) goto lab7;
                if (ret < 0) return ret;
            }
        lab7:
            z->c = c9;
        }
        {   int c10 = z->c; /* do, line 190 */
            if (!(z->I[0] > 2)) goto lab8; /* $(<integer expression> > <integer expression>), line 190 */
            z->lb = z->c; z->c = z->l; /* backwards, line 190 */

            {   int ret = r_remove_suffix(z); /* call remove_suffix, line 190 */
                if (ret == 0) goto lab8;
                if (ret < 0) return ret;
            }
            z->c = z->lb;
        lab8:
            z->c = c10;
        }
    }
lab4:
    return 1;
}