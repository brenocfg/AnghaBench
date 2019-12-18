#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_POLICY_LEVEL ;
typedef  int /*<<< orphan*/  X509_POLICY_DATA ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ X509_POLICY_CACHE ;

/* Variables and functions */
 int sk_X509_POLICY_DATA_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sk_X509_POLICY_DATA_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tree_link_matching_nodes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tree_link_nodes(X509_POLICY_LEVEL *curr,
                           const X509_POLICY_CACHE *cache)
{
    int i;

    for (i = 0; i < sk_X509_POLICY_DATA_num(cache->data); i++) {
        X509_POLICY_DATA *data = sk_X509_POLICY_DATA_value(cache->data, i);

        /* Look for matching nodes in previous level */
        if (!tree_link_matching_nodes(curr, data))
            return 0;
    }
    return 1;
}