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
typedef  scalar_t__ u64 ;
struct map {struct dso* dso; } ;
struct dso {int dummy; } ;
typedef  enum match_result { ____Placeholder_match_result } match_result ;

/* Variables and functions */
 int MATCH_EQ ; 
 int MATCH_GT ; 
 int MATCH_LT ; 

__attribute__((used)) static enum match_result match_chain_dso_addresses(struct map *left_map, u64 left_ip,
						   struct map *right_map, u64 right_ip)
{
	struct dso *left_dso = left_map ? left_map->dso : NULL;
	struct dso *right_dso = right_map ? right_map->dso : NULL;

	if (left_dso != right_dso)
		return left_dso < right_dso ? MATCH_LT : MATCH_GT;

	if (left_ip != right_ip)
 		return left_ip < right_ip ? MATCH_LT : MATCH_GT;

	return MATCH_EQ;
}