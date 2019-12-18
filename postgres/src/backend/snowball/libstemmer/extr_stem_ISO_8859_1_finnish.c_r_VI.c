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
struct SN_env {int c; int lb; char* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_V2 ; 
 scalar_t__ in_grouping_b (struct SN_env*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_VI(struct SN_env * z) { /* backwardmode */
    if (z->c <= z->lb || z->p[z->c - 1] != 'i') return 0; /* literal, line 94 */
    z->c--;
    if (in_grouping_b(z, g_V2, 97, 246, 0)) return 0; /* grouping V2, line 94 */
    return 1;
}