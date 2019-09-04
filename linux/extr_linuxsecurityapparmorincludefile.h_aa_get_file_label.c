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
struct aa_label {int dummy; } ;
struct aa_file_ctx {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 struct aa_label* aa_get_label_rcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct aa_label *aa_get_file_label(struct aa_file_ctx *ctx)
{
	return aa_get_label_rcu(&ctx->label);
}