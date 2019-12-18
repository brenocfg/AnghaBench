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
struct SN_env {int c; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_vowel ; 
 int out_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int r_more_than_one_syllable_word(struct SN_env * z) { /* forwardmode */
    {   int c_test1 = z->c; /* test, line 447 */
        {   int i = 2;
            while(1) { /* atleast, line 447 */
                int c2 = z->c;
                {    /* gopast */ /* grouping vowel, line 447 */
                    int ret = out_grouping_U(z, g_vowel, 97, 305, 1);
                    if (ret < 0) goto lab0;
                    z->c += ret;
                }
                i--;
                continue;
            lab0:
                z->c = c2;
                break;
            }
            if (i > 0) return 0;
        }
        z->c = c_test1;
    }
    return 1;
}