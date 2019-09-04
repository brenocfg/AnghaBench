#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xt_mtdtor_param {int /*<<< orphan*/  family; int /*<<< orphan*/  matchinfo; TYPE_1__* match; int /*<<< orphan*/  net; } ;
struct tcf_ematch {int /*<<< orphan*/  net; scalar_t__ data; } ;
struct em_ipt_match {TYPE_1__* match; int /*<<< orphan*/  match_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  me; int /*<<< orphan*/  (* destroy ) (struct xt_mtdtor_param*) ;int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xt_mtdtor_param*) ; 

__attribute__((used)) static void em_ipt_destroy(struct tcf_ematch *em)
{
	struct em_ipt_match *im = (void *)em->data;

	if (!im)
		return;

	if (im->match->destroy) {
		struct xt_mtdtor_param par = {
			.net = em->net,
			.match = im->match,
			.matchinfo = im->match_data,
			.family = im->match->family
		};
		im->match->destroy(&par);
	}
	module_put(im->match->me);
	kfree((void *)im);
}