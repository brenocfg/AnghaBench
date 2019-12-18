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
struct SN_env {scalar_t__ bra; scalar_t__ ket; scalar_t__ l; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 scalar_t__ SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (struct SN_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int slice_check(struct SN_env * z) {

    if (z->bra < 0 ||
        z->bra > z->ket ||
        z->ket > z->l ||
        z->p == NULL ||
        z->l > SIZE(z->p)) /* this line could be removed */
    {
#if 0
        fprintf(stderr, "faulty slice operation:\n");
        debug(z, -1, 0);
#endif
        return -1;
    }
    return 0;
}