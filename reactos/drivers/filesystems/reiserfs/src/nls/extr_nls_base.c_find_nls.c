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
struct nls_table {int /*<<< orphan*/  owner; int /*<<< orphan*/  charset; struct nls_table* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  _stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nls_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct nls_table* tables ; 
 int /*<<< orphan*/  try_inc_mod_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nls_table *find_nls(char *charset)
{
	struct nls_table *nls;
	spin_lock(&nls_lock);
	for (nls = tables; nls; nls = nls->next)
		if (! _stricmp(nls->charset, charset))
			break;
	if (nls && !try_inc_mod_count(nls->owner))
		nls = NULL;
	spin_unlock(&nls_lock);
	return nls;
}