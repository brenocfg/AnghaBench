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
struct SN_env {int ket; int c; int lb; char* p; int bra; } ;

/* Variables and functions */
 int r_R2 (struct SN_env*) ; 
 int slice_del (struct SN_env*) ; 

__attribute__((used)) static int r_Step_5b(struct SN_env * z) { /* backwardmode */
    z->ket = z->c; /* [, line 107 */
    if (z->c <= z->lb || z->p[z->c - 1] != 'l') return 0; /* literal, line 107 */
    z->c--;
    z->bra = z->c; /* ], line 107 */
    {   int ret = r_R2(z); /* call R2, line 108 */
        if (ret <= 0) return ret;
    }
    if (z->c <= z->lb || z->p[z->c - 1] != 'l') return 0; /* literal, line 108 */
    z->c--;
    {   int ret = slice_del(z); /* delete, line 109 */
        if (ret < 0) return ret;
    }
    return 1;
}