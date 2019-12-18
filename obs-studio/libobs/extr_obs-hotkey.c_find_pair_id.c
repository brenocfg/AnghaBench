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
struct obs_hotkey_internal_find_pair_forward {int member_1; size_t idx; int found; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_hotkey_pair_id ;

/* Variables and functions */
 int /*<<< orphan*/  enum_hotkey_pairs (int /*<<< orphan*/ ,struct obs_hotkey_internal_find_pair_forward*) ; 
 int /*<<< orphan*/  find_pair_id_helper ; 

__attribute__((used)) static inline bool find_pair_id(obs_hotkey_pair_id id, size_t *idx)
{
	struct obs_hotkey_internal_find_pair_forward find = {id, false, 0};
	enum_hotkey_pairs(find_pair_id_helper, &find);
	*idx = find.idx;
	return find.found;
}