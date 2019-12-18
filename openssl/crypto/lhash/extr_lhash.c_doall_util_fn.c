#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_nodes; TYPE_1__** b; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; struct TYPE_4__* next; } ;
typedef  TYPE_1__ OPENSSL_LH_NODE ;
typedef  int /*<<< orphan*/  (* OPENSSL_LH_DOALL_FUNCARG ) (int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  (* OPENSSL_LH_DOALL_FUNC ) (int /*<<< orphan*/ ) ;
typedef  TYPE_2__ OPENSSL_LHASH ;

/* Variables and functions */

__attribute__((used)) static void doall_util_fn(OPENSSL_LHASH *lh, int use_arg,
                          OPENSSL_LH_DOALL_FUNC func,
                          OPENSSL_LH_DOALL_FUNCARG func_arg, void *arg)
{
    int i;
    OPENSSL_LH_NODE *a, *n;

    if (lh == NULL)
        return;

    /*
     * reverse the order so we search from 'top to bottom' We were having
     * memory leaks otherwise
     */
    for (i = lh->num_nodes - 1; i >= 0; i--) {
        a = lh->b[i];
        while (a != NULL) {
            n = a->next;
            if (use_arg)
                func_arg(a->data, arg);
            else
                func(a->data);
            a = n;
        }
    }
}