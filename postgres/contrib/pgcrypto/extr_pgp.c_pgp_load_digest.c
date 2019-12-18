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
typedef  int /*<<< orphan*/  PX_MD ;

/* Variables and functions */
 int PXE_PGP_CORRUPT_DATA ; 
 int PXE_PGP_UNSUPPORTED_HASH ; 
 char* pgp_get_digest_name (int) ; 
 int px_find_digest (char const*,int /*<<< orphan*/ **) ; 

int
pgp_load_digest(int code, PX_MD **res)
{
	int			err;
	const char *name = pgp_get_digest_name(code);

	if (name == NULL)
		return PXE_PGP_CORRUPT_DATA;

	err = px_find_digest(name, res);
	if (err == 0)
		return 0;

	return PXE_PGP_UNSUPPORTED_HASH;
}