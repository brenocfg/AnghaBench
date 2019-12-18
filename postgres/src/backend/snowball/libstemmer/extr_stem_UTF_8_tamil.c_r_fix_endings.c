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
 int r_fix_ending (struct SN_env*) ; 

__attribute__((used)) static int r_fix_endings(struct SN_env * z) { /* forwardmode */
    {   int c1 = z->c; /* do, line 111 */
        while(1) { /* repeat, line 111 */
            int c2 = z->c;
            {   int ret = r_fix_ending(z); /* call fix_ending, line 111 */
                if (ret == 0) goto lab1;
                if (ret < 0) return ret;
            }
            continue;
        lab1:
            z->c = c2;
            break;
        }
        z->c = c1;
    }
    return 1;
}