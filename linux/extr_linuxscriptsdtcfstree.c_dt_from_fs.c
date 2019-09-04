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
struct node {int dummy; } ;
struct dt_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSF_V1 ; 
 struct dt_info* build_dt_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guess_boot_cpuid (struct node*) ; 
 struct node* name_node (struct node*,char*) ; 
 struct node* read_fstree (char const*) ; 

struct dt_info *dt_from_fs(const char *dirname)
{
	struct node *tree;

	tree = read_fstree(dirname);
	tree = name_node(tree, "");

	return build_dt_info(DTSF_V1, NULL, tree, guess_boot_cpuid(tree));
}