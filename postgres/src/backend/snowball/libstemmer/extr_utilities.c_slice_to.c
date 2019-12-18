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
typedef  int /*<<< orphan*/  symbol ;
struct SN_env {int ket; int bra; int p; } ;

/* Variables and functions */
 int CAPACITY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_SIZE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * increase_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lose_s (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ slice_check (struct SN_env*) ; 

extern symbol * slice_to(struct SN_env * z, symbol * p) {
    if (slice_check(z)) {
        lose_s(p);
        return NULL;
    }
    {
        int len = z->ket - z->bra;
        if (CAPACITY(p) < len) {
            p = increase_size(p, len);
            if (p == NULL)
                return NULL;
        }
        memmove(p, z->p + z->bra, len * sizeof(symbol));
        SET_SIZE(p, len);
    }
    return p;
}