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
struct SN_env {int l; int c; int lb; int* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_2 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r_double(struct SN_env * z) { /* backwardmode */
    {   int m_test1 = z->l - z->c; /* test, line 68 */
        if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((106790108 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* among, line 68 */
        if (!(find_among_b(z, a_2, 23))) return 0;
        z->c = z->l - m_test1;
    }
    return 1;
}