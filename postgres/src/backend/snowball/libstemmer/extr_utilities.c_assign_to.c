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
struct SN_env {int l; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int CAPACITY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_SIZE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * increase_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

extern symbol * assign_to(struct SN_env * z, symbol * p) {
    int len = z->l;
    if (CAPACITY(p) < len) {
        p = increase_size(p, len);
        if (p == NULL)
            return NULL;
    }
    memmove(p, z->p, len * sizeof(symbol));
    SET_SIZE(p, len);
    return p;
}