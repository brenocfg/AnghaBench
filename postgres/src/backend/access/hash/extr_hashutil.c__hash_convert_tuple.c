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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  UInt32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_datum2hashkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
_hash_convert_tuple(Relation index,
					Datum *user_values, bool *user_isnull,
					Datum *index_values, bool *index_isnull)
{
	uint32		hashkey;

	/*
	 * We do not insert null values into hash indexes.  This is okay because
	 * the only supported search operator is '=', and we assume it is strict.
	 */
	if (user_isnull[0])
		return false;

	hashkey = _hash_datum2hashkey(index, user_values[0]);
	index_values[0] = UInt32GetDatum(hashkey);
	index_isnull[0] = false;
	return true;
}