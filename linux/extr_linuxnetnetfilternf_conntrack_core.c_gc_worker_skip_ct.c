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
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_is_confirmed (struct nf_conn const*) ; 
 scalar_t__ nf_ct_is_dying (struct nf_conn const*) ; 

__attribute__((used)) static bool gc_worker_skip_ct(const struct nf_conn *ct)
{
	return !nf_ct_is_confirmed(ct) || nf_ct_is_dying(ct);
}