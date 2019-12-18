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
typedef  int /*<<< orphan*/  PushFilter ;
typedef  int /*<<< orphan*/  PX_MD ;

/* Variables and functions */
 int /*<<< orphan*/  PGP_DIGEST_SHA1 ; 
 int pgp_load_digest (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
mdc_init(PushFilter *dst, void *init_arg, void **priv_p)
{
	int			res;
	PX_MD	   *md;

	res = pgp_load_digest(PGP_DIGEST_SHA1, &md);
	if (res < 0)
		return res;

	*priv_p = md;
	return 0;
}