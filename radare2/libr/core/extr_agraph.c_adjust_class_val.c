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
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  int /*<<< orphan*/  RAGraph ;

/* Variables and functions */
 int dist_nodes (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int hash_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int adjust_class_val(const RAGraph *g, const RGraphNode *gn, const RGraphNode *sibl, Sdb *res, int is_left) {
	if (is_left) {
		return hash_get_int (res, sibl) - hash_get_int (res, gn) - dist_nodes (g, gn, sibl);
	}
	return hash_get_int (res, gn) - hash_get_int (res, sibl) - dist_nodes (g, sibl, gn);
}