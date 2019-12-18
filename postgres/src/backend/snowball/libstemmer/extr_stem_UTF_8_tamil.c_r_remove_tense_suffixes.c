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
struct SN_env {int* B; int c; } ;

/* Variables and functions */
 int r_remove_tense_suffix (struct SN_env*) ; 

__attribute__((used)) static int r_remove_tense_suffixes(struct SN_env * z) { /* forwardmode */
    z->B[0] = 1; /* set found_a_match, line 305 */
    while(1) { /* repeat, line 306 */
        int c1 = z->c;
        if (!(z->B[0])) goto lab0; /* Boolean test found_a_match, line 306 */
        {   int c2 = z->c; /* do, line 306 */
            {   int ret = r_remove_tense_suffix(z); /* call remove_tense_suffix, line 306 */
                if (ret == 0) goto lab1;
                if (ret < 0) return ret;
            }
        lab1:
            z->c = c2;
        }
        continue;
    lab0:
        z->c = c1;
        break;
    }
    return 1;
}