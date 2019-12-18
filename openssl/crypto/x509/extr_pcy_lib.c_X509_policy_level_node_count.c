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
struct TYPE_3__ {scalar_t__ nodes; scalar_t__ anyPolicy; } ;
typedef  TYPE_1__ X509_POLICY_LEVEL ;

/* Variables and functions */
 scalar_t__ sk_X509_POLICY_NODE_num (scalar_t__) ; 

int X509_policy_level_node_count(X509_POLICY_LEVEL *level)
{
    int n;
    if (!level)
        return 0;
    if (level->anyPolicy)
        n = 1;
    else
        n = 0;
    if (level->nodes)
        n += sk_X509_POLICY_NODE_num(level->nodes);
    return n;
}