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
struct SN_env {int* I; int l; int c; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_v ; 
 int in_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int out_grouping_U (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int skip_utf8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int r_mark_regions(struct SN_env * z) { /* forwardmode */
    z->I[0] = z->l; /* $pV = <integer expression>, line 40 */
    z->I[1] = z->l; /* $p1 = <integer expression>, line 41 */
    z->I[2] = z->l; /* $p2 = <integer expression>, line 42 */
    {   int c1 = z->c; /* do, line 44 */
        {   int c2 = z->c; /* or, line 46 */
            if (in_grouping_U(z, g_v, 97, 259, 0)) goto lab2; /* grouping v, line 45 */
            {   int c3 = z->c; /* or, line 45 */
                if (out_grouping_U(z, g_v, 97, 259, 0)) goto lab4; /* non v, line 45 */
                {    /* gopast */ /* grouping v, line 45 */
                    int ret = out_grouping_U(z, g_v, 97, 259, 1);
                    if (ret < 0) goto lab4;
                    z->c += ret;
                }
                goto lab3;
            lab4:
                z->c = c3;
                if (in_grouping_U(z, g_v, 97, 259, 0)) goto lab2; /* grouping v, line 45 */
                {    /* gopast */ /* non v, line 45 */
                    int ret = in_grouping_U(z, g_v, 97, 259, 1);
                    if (ret < 0) goto lab2;
                    z->c += ret;
                }
            }
        lab3:
            goto lab1;
        lab2:
            z->c = c2;
            if (out_grouping_U(z, g_v, 97, 259, 0)) goto lab0; /* non v, line 47 */
            {   int c4 = z->c; /* or, line 47 */
                if (out_grouping_U(z, g_v, 97, 259, 0)) goto lab6; /* non v, line 47 */
                {    /* gopast */ /* grouping v, line 47 */
                    int ret = out_grouping_U(z, g_v, 97, 259, 1);
                    if (ret < 0) goto lab6;
                    z->c += ret;
                }
                goto lab5;
            lab6:
                z->c = c4;
                if (in_grouping_U(z, g_v, 97, 259, 0)) goto lab0; /* grouping v, line 47 */
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab0;
                    z->c = ret; /* next, line 47 */
                }
            }
        lab5:
            ;
        }
    lab1:
        z->I[0] = z->c; /* setmark pV, line 48 */
    lab0:
        z->c = c1;
    }
    {   int c5 = z->c; /* do, line 50 */
        {    /* gopast */ /* grouping v, line 51 */
            int ret = out_grouping_U(z, g_v, 97, 259, 1);
            if (ret < 0) goto lab7;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 51 */
            int ret = in_grouping_U(z, g_v, 97, 259, 1);
            if (ret < 0) goto lab7;
            z->c += ret;
        }
        z->I[1] = z->c; /* setmark p1, line 51 */
        {    /* gopast */ /* grouping v, line 52 */
            int ret = out_grouping_U(z, g_v, 97, 259, 1);
            if (ret < 0) goto lab7;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 52 */
            int ret = in_grouping_U(z, g_v, 97, 259, 1);
            if (ret < 0) goto lab7;
            z->c += ret;
        }
        z->I[2] = z->c; /* setmark p2, line 52 */
    lab7:
        z->c = c5;
    }
    return 1;
}