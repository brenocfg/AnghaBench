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
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509_POLICY_TREE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get0_policy_tree (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_explicit_policy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_policy_tree_get0_policies (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_policy_tree_get0_user_policies (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  nodes_print (char*,int /*<<< orphan*/ ) ; 

void policies_print(X509_STORE_CTX *ctx)
{
    X509_POLICY_TREE *tree;
    int explicit_policy;
    tree = X509_STORE_CTX_get0_policy_tree(ctx);
    explicit_policy = X509_STORE_CTX_get_explicit_policy(ctx);

    BIO_printf(bio_err, "Require explicit Policy: %s\n",
               explicit_policy ? "True" : "False");

    nodes_print("Authority", X509_policy_tree_get0_policies(tree));
    nodes_print("User", X509_policy_tree_get0_user_policies(tree));
}