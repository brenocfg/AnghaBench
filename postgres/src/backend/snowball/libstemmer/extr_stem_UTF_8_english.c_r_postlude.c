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
struct SN_env {int c; int bra; int l; char* p; size_t ket; int /*<<< orphan*/ * B; } ;

/* Variables and functions */
 int /*<<< orphan*/  s_38 ; 
 int skip_utf8 (char*,int,int /*<<< orphan*/ ,int,int) ; 
 int slice_from_s (struct SN_env*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_postlude(struct SN_env * z) { /* forwardmode */
    if (!(z->B[0])) return 0; /* Boolean test Y_found, line 203 */
    while(1) { /* repeat, line 203 */
        int c1 = z->c;
        while(1) { /* goto, line 203 */
            int c2 = z->c;
            z->bra = z->c; /* [, line 203 */
            if (z->c == z->l || z->p[z->c] != 'Y') goto lab1; /* literal, line 203 */
            z->c++;
            z->ket = z->c; /* ], line 203 */
            z->c = c2;
            break;
        lab1:
            z->c = c2;
            {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                if (ret < 0) goto lab0;
                z->c = ret; /* goto, line 203 */
            }
        }
        {   int ret = slice_from_s(z, 1, s_38); /* <-, line 203 */
            if (ret < 0) return ret;
        }
        continue;
    lab0:
        z->c = c1;
        break;
    }
    return 1;
}