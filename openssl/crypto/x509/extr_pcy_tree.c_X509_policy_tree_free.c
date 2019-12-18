#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nlevel; struct TYPE_5__* levels; int /*<<< orphan*/  extra_data; int /*<<< orphan*/  anyPolicy; int /*<<< orphan*/  nodes; int /*<<< orphan*/  cert; int /*<<< orphan*/  user_policies; int /*<<< orphan*/  auth_policies; } ;
typedef  TYPE_1__ X509_POLICY_TREE ;
typedef  TYPE_1__ X509_POLICY_LEVEL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exnode_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_data_free ; 
 int /*<<< orphan*/  policy_node_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_POLICY_DATA_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_POLICY_NODE_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_POLICY_NODE_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 

void X509_policy_tree_free(X509_POLICY_TREE *tree)
{
    X509_POLICY_LEVEL *curr;
    int i;

    if (!tree)
        return;

    sk_X509_POLICY_NODE_free(tree->auth_policies);
    sk_X509_POLICY_NODE_pop_free(tree->user_policies, exnode_free);

    for (i = 0, curr = tree->levels; i < tree->nlevel; i++, curr++) {
        X509_free(curr->cert);
        sk_X509_POLICY_NODE_pop_free(curr->nodes, policy_node_free);
        policy_node_free(curr->anyPolicy);
    }

    sk_X509_POLICY_DATA_pop_free(tree->extra_data, policy_data_free);
    OPENSSL_free(tree->levels);
    OPENSSL_free(tree);

}