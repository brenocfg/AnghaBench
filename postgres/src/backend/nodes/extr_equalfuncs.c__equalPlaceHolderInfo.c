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
typedef  int /*<<< orphan*/  PlaceHolderInfo ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ph_eval_at ; 
 int /*<<< orphan*/  ph_lateral ; 
 int /*<<< orphan*/  ph_needed ; 
 int /*<<< orphan*/  ph_var ; 
 int /*<<< orphan*/  ph_width ; 
 int /*<<< orphan*/  phid ; 

__attribute__((used)) static bool
_equalPlaceHolderInfo(const PlaceHolderInfo *a, const PlaceHolderInfo *b)
{
	COMPARE_SCALAR_FIELD(phid);
	COMPARE_NODE_FIELD(ph_var); /* should be redundant */
	COMPARE_BITMAPSET_FIELD(ph_eval_at);
	COMPARE_BITMAPSET_FIELD(ph_lateral);
	COMPARE_BITMAPSET_FIELD(ph_needed);
	COMPARE_SCALAR_FIELD(ph_width);

	return true;
}