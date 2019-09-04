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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  gimple_stmt_iterator ;
typedef  int /*<<< orphan*/  gimple ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  GSI_NEW_STMT ; 
 int /*<<< orphan*/  add_referenced_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_assign (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_var (int /*<<< orphan*/ ,char*) ; 
 int get_op (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimple_build_assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_insert_after (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latent_entropy_decl ; 
 int /*<<< orphan*/  long_unsigned_type_node ; 
 int /*<<< orphan*/  mark_sym_for_renaming (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __perturb_latent_entropy(gimple_stmt_iterator *gsi,
					tree local_entropy)
{
	gimple assign;
	tree temp;
	enum tree_code op;

	/* 1. create temporary copy of latent_entropy */
	temp = create_var(long_unsigned_type_node, "temp_latent_entropy");

	/* 2. read... */
	add_referenced_var(latent_entropy_decl);
	mark_sym_for_renaming(latent_entropy_decl);
	assign = gimple_build_assign(temp, latent_entropy_decl);
	gsi_insert_before(gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);

	/* 3. ...modify... */
	op = get_op(NULL);
	assign = create_assign(op, temp, temp, local_entropy);
	gsi_insert_after(gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);

	/* 4. ...write latent_entropy */
	assign = gimple_build_assign(latent_entropy_decl, temp);
	gsi_insert_after(gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);
}