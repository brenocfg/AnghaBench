#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const bytea ;
struct TYPE_3__ {int /*<<< orphan*/  const* lower; int /*<<< orphan*/  const* upper; } ;
typedef  TYPE_1__ GBT_VARKEY_R ;
typedef  int /*<<< orphan*/  GBT_VARKEY ;

/* Variables and functions */
 size_t INTALIGN (scalar_t__) ; 
 size_t VARHDRSZ ; 
 scalar_t__ VARSIZE (int /*<<< orphan*/  const*) ; 

GBT_VARKEY_R
gbt_var_key_readable(const GBT_VARKEY *k)
{
	GBT_VARKEY_R r;

	r.lower = (bytea *) &(((char *) k)[VARHDRSZ]);
	if (VARSIZE(k) > (VARHDRSZ + (VARSIZE(r.lower))))
		r.upper = (bytea *) &(((char *) k)[VARHDRSZ + INTALIGN(VARSIZE(r.lower))]);
	else
		r.upper = r.lower;
	return r;
}