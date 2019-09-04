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
struct nfs_open_context {scalar_t__ cred; scalar_t__ state; } ;

/* Variables and functions */

__attribute__((used)) static inline bool nfs_match_open_context(const struct nfs_open_context *ctx1,
		const struct nfs_open_context *ctx2)
{
	return ctx1->cred == ctx2->cred && ctx1->state == ctx2->state;
}