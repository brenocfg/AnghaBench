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
struct SN_env {int c; int lb; int* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_1 ; 
 int /*<<< orphan*/  find_among_b (struct SN_env*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r_mark_lArI(struct SN_env * z) { /* backwardmode */
    if (z->c - 3 <= z->lb || (z->p[z->c - 1] != 105 && z->p[z->c - 1] != 177)) return 0; /* among, line 177 */
    if (!(find_among_b(z, a_1, 2))) return 0;
    return 1;
}