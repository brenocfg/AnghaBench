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
struct int_digest {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;scalar_t__ name; } ;
typedef  int /*<<< orphan*/  PX_MD ;

/* Variables and functions */
 int PXE_NO_HASH ; 
 struct int_digest* int_digest_list ; 
 scalar_t__ pg_strcasecmp (scalar_t__,char const*) ; 
 int /*<<< orphan*/ * px_alloc (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

int
px_find_digest(const char *name, PX_MD **res)
{
	const struct int_digest *p;
	PX_MD	   *h;

	for (p = int_digest_list; p->name; p++)
		if (pg_strcasecmp(p->name, name) == 0)
		{
			h = px_alloc(sizeof(*h));
			p->init(h);

			*res = h;

			return 0;
		}
	return PXE_NO_HASH;
}