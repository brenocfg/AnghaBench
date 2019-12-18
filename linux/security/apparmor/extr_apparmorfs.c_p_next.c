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
struct seq_file {struct aa_ns* private; } ;
struct aa_profile {int dummy; } ;
struct aa_ns {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* next_profile (struct aa_ns*,struct aa_profile*) ; 

__attribute__((used)) static void *p_next(struct seq_file *f, void *p, loff_t *pos)
{
	struct aa_profile *profile = p;
	struct aa_ns *ns = f->private;
	(*pos)++;

	return next_profile(ns, profile);
}