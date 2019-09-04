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
struct qstr {unsigned char* name; unsigned int len; int /*<<< orphan*/  hash; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_VARIABLE_GUID_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  efivarfs_valid_name (unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  end_name_hash (unsigned long) ; 
 unsigned long init_name_hash (struct dentry const*) ; 
 unsigned long partial_name_hash (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efivarfs_d_hash(const struct dentry *dentry, struct qstr *qstr)
{
	unsigned long hash = init_name_hash(dentry);
	const unsigned char *s = qstr->name;
	unsigned int len = qstr->len;

	if (!efivarfs_valid_name(s, len))
		return -EINVAL;

	while (len-- > EFI_VARIABLE_GUID_LEN)
		hash = partial_name_hash(*s++, hash);

	/* GUID is case-insensitive. */
	while (len--)
		hash = partial_name_hash(tolower(*s++), hash);

	qstr->hash = end_name_hash(hash);
	return 0;
}