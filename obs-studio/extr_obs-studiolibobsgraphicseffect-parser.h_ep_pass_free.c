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
struct ep_pass {int /*<<< orphan*/  fragment_program; int /*<<< orphan*/  vertex_program; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ep_pass_free(struct ep_pass *epp)
{
	bfree(epp->name);
	da_free(epp->vertex_program);
	da_free(epp->fragment_program);
}