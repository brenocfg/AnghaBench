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
struct bfa_uf_s {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_UF_MOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_uf_post_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_uf_put (int /*<<< orphan*/ ,struct bfa_uf_s*) ; 

void
bfa_uf_free(struct bfa_uf_s *uf)
{
	bfa_uf_put(BFA_UF_MOD(uf->bfa), uf);
	bfa_uf_post_all(BFA_UF_MOD(uf->bfa));
}