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
struct SN_env {int /*<<< orphan*/  c; int /*<<< orphan*/  bra; int /*<<< orphan*/  ket; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_23 ; 
 int find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_5 ; 
 int /*<<< orphan*/  s_6 ; 
 int /*<<< orphan*/  s_7 ; 
 int /*<<< orphan*/  s_8 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_post_process_last_consonants(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 414 */
    among_var = find_among_b(z, a_23, 4); /* substring, line 414 */
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 414 */
    switch (among_var) { /* among, line 414 */
        case 1:
            {   int ret = slice_from_s(z, 1, s_5); /* <-, line 415 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 2, s_6); /* <-, line 416 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 1, s_7); /* <-, line 417 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = slice_from_s(z, 1, s_8); /* <-, line 418 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}