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
typedef  int int32 ;
typedef  int /*<<< orphan*/  gbtree_vinfo ;
struct TYPE_3__ {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; } ;
typedef  TYPE_1__ GBT_VARKEY_R ;
typedef  char GBT_VARKEY ;

/* Variables and functions */
 int INTALIGN (int) ; 
 int Min (int,int) ; 
 int /*<<< orphan*/  SET_VARSIZE (char*,int) ; 
 char* VARDATA (char*) ; 
 int VARHDRSZ ; 
 int VARSIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__ gbt_var_key_readable (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static GBT_VARKEY *
gbt_var_node_truncate(const GBT_VARKEY *node, int32 cpf_length, const gbtree_vinfo *tinfo)
{
	GBT_VARKEY *out = NULL;
	GBT_VARKEY_R r = gbt_var_key_readable(node);
	int32		len1 = VARSIZE(r.lower) - VARHDRSZ;
	int32		len2 = VARSIZE(r.upper) - VARHDRSZ;
	int32		si;
	char	   *out2;

	len1 = Min(len1, (cpf_length + 1));
	len2 = Min(len2, (cpf_length + 1));

	si = 2 * VARHDRSZ + INTALIGN(len1 + VARHDRSZ) + len2;
	out = (GBT_VARKEY *) palloc0(si);
	SET_VARSIZE(out, si);

	memcpy(VARDATA(out), r.lower, len1 + VARHDRSZ);
	SET_VARSIZE(VARDATA(out), len1 + VARHDRSZ);

	out2 = VARDATA(out) + INTALIGN(len1 + VARHDRSZ);
	memcpy(out2, r.upper, len2 + VARHDRSZ);
	SET_VARSIZE(out2, len2 + VARHDRSZ);

	return out;
}