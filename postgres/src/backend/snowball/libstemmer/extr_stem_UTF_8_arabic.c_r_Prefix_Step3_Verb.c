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
struct SN_env {int /*<<< orphan*/  p; int /*<<< orphan*/  c; int /*<<< orphan*/  ket; int /*<<< orphan*/  bra; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_8 ; 
 int find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int len_utf8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_63 ; 
 int /*<<< orphan*/  s_64 ; 
 int /*<<< orphan*/  s_65 ; 
 int /*<<< orphan*/  s_66 ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_Prefix_Step3_Verb(struct SN_env * z) { /* forwardmode */
    int among_var;
    z->bra = z->c; /* [, line 392 */
    among_var = find_among(z, a_8, 4); /* substring, line 392 */
    if (!(among_var)) return 0;
    z->ket = z->c; /* ], line 392 */
    switch (among_var) { /* among, line 392 */
        case 1:
            if (!(len_utf8(z->p) > 4)) return 0; /* $(<integer expression> > <integer expression>), line 394 */
            {   int ret = slice_from_s(z, 2, s_63); /* <-, line 394 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            if (!(len_utf8(z->p) > 4)) return 0; /* $(<integer expression> > <integer expression>), line 395 */
            {   int ret = slice_from_s(z, 2, s_64); /* <-, line 395 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            if (!(len_utf8(z->p) > 4)) return 0; /* $(<integer expression> > <integer expression>), line 396 */
            {   int ret = slice_from_s(z, 2, s_65); /* <-, line 396 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            if (!(len_utf8(z->p) > 4)) return 0; /* $(<integer expression> > <integer expression>), line 397 */
            {   int ret = slice_from_s(z, 2, s_66); /* <-, line 397 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}