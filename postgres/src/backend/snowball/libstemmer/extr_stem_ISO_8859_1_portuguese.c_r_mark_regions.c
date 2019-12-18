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
struct SN_env {int* I; int l; int c; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_v ; 
 int in_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 
 int out_grouping (struct SN_env*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int r_mark_regions(struct SN_env * z) { /* forwardmode */
    z->I[0] = z->l; /* $pV = <integer expression>, line 46 */
    z->I[1] = z->l; /* $p1 = <integer expression>, line 47 */
    z->I[2] = z->l; /* $p2 = <integer expression>, line 48 */
    {   int c1 = z->c; /* do, line 50 */
        {   int c2 = z->c; /* or, line 52 */
            if (in_grouping(z, g_v, 97, 250, 0)) goto lab2; /* grouping v, line 51 */
            {   int c3 = z->c; /* or, line 51 */
                if (out_grouping(z, g_v, 97, 250, 0)) goto lab4; /* non v, line 51 */
                {    /* gopast */ /* grouping v, line 51 */
                    int ret = out_grouping(z, g_v, 97, 250, 1);
                    if (ret < 0) goto lab4;
                    z->c += ret;
                }
                goto lab3;
            lab4:
                z->c = c3;
                if (in_grouping(z, g_v, 97, 250, 0)) goto lab2; /* grouping v, line 51 */
                {    /* gopast */ /* non v, line 51 */
                    int ret = in_grouping(z, g_v, 97, 250, 1);
                    if (ret < 0) goto lab2;
                    z->c += ret;
                }
            }
        lab3:
            goto lab1;
        lab2:
            z->c = c2;
            if (out_grouping(z, g_v, 97, 250, 0)) goto lab0; /* non v, line 53 */
            {   int c4 = z->c; /* or, line 53 */
                if (out_grouping(z, g_v, 97, 250, 0)) goto lab6; /* non v, line 53 */
                {    /* gopast */ /* grouping v, line 53 */
                    int ret = out_grouping(z, g_v, 97, 250, 1);
                    if (ret < 0) goto lab6;
                    z->c += ret;
                }
                goto lab5;
            lab6:
                z->c = c4;
                if (in_grouping(z, g_v, 97, 250, 0)) goto lab0; /* grouping v, line 53 */
                if (z->c >= z->l) goto lab0;
                z->c++; /* next, line 53 */
            }
        lab5:
            ;
        }
    lab1:
        z->I[0] = z->c; /* setmark pV, line 54 */
    lab0:
        z->c = c1;
    }
    {   int c5 = z->c; /* do, line 56 */
        {    /* gopast */ /* grouping v, line 57 */
            int ret = out_grouping(z, g_v, 97, 250, 1);
            if (ret < 0) goto lab7;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 57 */
            int ret = in_grouping(z, g_v, 97, 250, 1);
            if (ret < 0) goto lab7;
            z->c += ret;
        }
        z->I[1] = z->c; /* setmark p1, line 57 */
        {    /* gopast */ /* grouping v, line 58 */
            int ret = out_grouping(z, g_v, 97, 250, 1);
            if (ret < 0) goto lab7;
            z->c += ret;
        }
        {    /* gopast */ /* non v, line 58 */
            int ret = in_grouping(z, g_v, 97, 250, 1);
            if (ret < 0) goto lab7;
            z->c += ret;
        }
        z->I[2] = z->c; /* setmark p2, line 58 */
    lab7:
        z->c = c5;
    }
    return 1;
}