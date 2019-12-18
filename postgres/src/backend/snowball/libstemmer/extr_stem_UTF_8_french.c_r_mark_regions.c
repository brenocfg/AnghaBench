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
struct SN_env {int* I; int l; int c; int* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_0 ; 
 int /*<<< orphan*/  find_among (struct SN_env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_v ; 
 int in_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int out_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int skip_utf8 (int*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int r_mark_regions(struct SN_env * z) { /* forwardmode */
    z->I[0] = z->l; /* $pV = <integer expression>, line 56 */
    z->I[1] = z->l; /* $p1 = <integer expression>, line 57 */
    z->I[2] = z->l; /* $p2 = <integer expression>, line 58 */
    {   int c1 = z->c; /* do, line 60 */
        {   int c2 = z->c; /* or, line 62 */
            if (in_grouping_U(z, g_v, 97, 251, 0)) goto lab2; /* grouping v, line 61 */
            if (in_grouping_U(z, g_v, 97, 251, 0)) goto lab2; /* grouping v, line 61 */
            {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                if (ret < 0) goto lab2;
                z->c = ret; /* next, line 61 */
            }
            goto lab1;
        lab2:
            z->c = c2;
            if (z->c + 2 >= z->l || z->p[z->c + 2] >> 5 != 3 || !((331776 >> (z->p[z->c + 2] & 0x1f)) & 1)) goto lab3; /* among, line 63 */
            if (!(find_among(z, a_0, 3))) goto lab3;
            goto lab1;
        lab3:
            z->c = c2;
            {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                if (ret < 0) goto lab0;
                z->c = ret; /* next, line 70 */
            }
            {    /* gopast */ /* grouping v, line 70 */
                int ret = out_grouping_U(z, g_v, 97, 251, 1);
                if (ret < 0) goto lab0;
                z->c += ret;
            }
        }
    lab1:
        z->I[0] = z->c; /* setmark pV, line 71 */
    lab0:
        z->c = c1;
    }
    {   int c3 = z->c; /* do, line 73 */
        {    /* gopast */ /* grouping v, line 74 */
            int ret = out_grouping_U(z, g_v, 97, 251, 1);
            if (ret < 0) goto lab4;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 74 */
            int ret = in_grouping_U(z, g_v, 97, 251, 1);
            if (ret < 0) goto lab4;
            z->c += ret;
        }
        z->I[1] = z->c; /* setmark p1, line 74 */
        {    /* gopast */ /* grouping v, line 75 */
            int ret = out_grouping_U(z, g_v, 97, 251, 1);
            if (ret < 0) goto lab4;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 75 */
            int ret = in_grouping_U(z, g_v, 97, 251, 1);
            if (ret < 0) goto lab4;
            z->c += ret;
        }
        z->I[2] = z->c; /* setmark p2, line 75 */
    lab4:
        z->c = c3;
    }
    return 1;
}