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
struct aa_label {int size; int /*<<< orphan*/  node; int /*<<< orphan*/  count; int /*<<< orphan*/ ** vec; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ aa_alloc_secid (struct aa_label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

bool aa_label_init(struct aa_label *label, int size, gfp_t gfp)
{
	AA_BUG(!label);
	AA_BUG(size < 1);

	if (aa_alloc_secid(label, gfp) < 0)
		return false;

	label->size = size;			/* doesn't include null */
	label->vec[size] = NULL;		/* null terminate */
	kref_init(&label->count);
	RB_CLEAR_NODE(&label->node);

	return true;
}