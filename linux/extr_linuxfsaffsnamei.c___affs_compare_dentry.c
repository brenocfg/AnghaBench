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
typedef  char u8 ;
typedef  scalar_t__ (* toupper_t ) (int /*<<< orphan*/ ) ;
struct qstr {char* name; unsigned int len; } ;

/* Variables and functions */
 unsigned int AFFSNAMEMAX ; 
 scalar_t__ affs_check_name (char*,unsigned int,int) ; 

__attribute__((used)) static inline int __affs_compare_dentry(unsigned int len,
		const char *str, const struct qstr *name, toupper_t toupper,
		bool notruncate)
{
	const u8 *aname = str;
	const u8 *bname = name->name;

	/*
	 * 'str' is the name of an already existing dentry, so the name
	 * must be valid. 'name' must be validated first.
	 */

	if (affs_check_name(name->name, name->len, notruncate))
		return 1;

	/*
	 * If the names are longer than the allowed 30 chars,
	 * the excess is ignored, so their length may differ.
	 */
	if (len >= AFFSNAMEMAX) {
		if (name->len < AFFSNAMEMAX)
			return 1;
		len = AFFSNAMEMAX;
	} else if (len != name->len)
		return 1;

	for (; len > 0; len--)
		if (toupper(*aname++) != toupper(*bname++))
			return 1;

	return 0;
}