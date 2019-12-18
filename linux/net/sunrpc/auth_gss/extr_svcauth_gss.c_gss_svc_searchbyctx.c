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
struct xdr_netobj {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rsc {int /*<<< orphan*/  h; int /*<<< orphan*/  handle; } ;
struct cache_detail {int dummy; } ;
typedef  int /*<<< orphan*/  rsci ;

/* Variables and functions */
 scalar_t__ cache_check (struct cache_detail*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dup_to_netobj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rsc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rsc_free (struct rsc*) ; 
 struct rsc* rsc_lookup (struct cache_detail*,struct rsc*) ; 

__attribute__((used)) static struct rsc *
gss_svc_searchbyctx(struct cache_detail *cd, struct xdr_netobj *handle)
{
	struct rsc rsci;
	struct rsc *found;

	memset(&rsci, 0, sizeof(rsci));
	if (dup_to_netobj(&rsci.handle, handle->data, handle->len))
		return NULL;
	found = rsc_lookup(cd, &rsci);
	rsc_free(&rsci);
	if (!found)
		return NULL;
	if (cache_check(cd, &found->h, NULL))
		return NULL;
	return found;
}