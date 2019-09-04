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
struct fl_flow_mask {int dummy; } ;
struct fl_flow_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fl_key_get_start (struct fl_flow_key*,struct fl_flow_mask*) ; 
 int /*<<< orphan*/  fl_mask_range (struct fl_flow_mask*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fl_clear_masked_range(struct fl_flow_key *key,
				  struct fl_flow_mask *mask)
{
	memset(fl_key_get_start(key, mask), 0, fl_mask_range(mask));
}