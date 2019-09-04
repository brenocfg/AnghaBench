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
struct ubifs_info {int dummy; } ;
struct ubifs_dent_node {int /*<<< orphan*/  name; int /*<<< orphan*/  nlen; } ;
struct fscrypt_name {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dbg_is_chk_gen (struct ubifs_info const*) ; 
 scalar_t__ fname_len (struct fscrypt_name const*) ; 
 int /*<<< orphan*/  fname_name (struct fscrypt_name const*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dbg_check_name(const struct ubifs_info *c,
			  const struct ubifs_dent_node *dent,
			  const struct fscrypt_name *nm)
{
	if (!dbg_is_chk_gen(c))
		return 0;
	if (le16_to_cpu(dent->nlen) != fname_len(nm))
		return -EINVAL;
	if (memcmp(dent->name, fname_name(nm), fname_len(nm)))
		return -EINVAL;
	return 0;
}