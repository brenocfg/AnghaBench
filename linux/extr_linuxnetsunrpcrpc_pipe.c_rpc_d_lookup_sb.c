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
struct super_block {int /*<<< orphan*/  s_root; } ;
struct qstr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct qstr QSTR_INIT (unsigned char const*,int /*<<< orphan*/ ) ; 
 struct dentry* d_hash_and_lookup (int /*<<< orphan*/ ,struct qstr*) ; 
 int /*<<< orphan*/  strlen (unsigned char const*) ; 

struct dentry *rpc_d_lookup_sb(const struct super_block *sb,
			       const unsigned char *dir_name)
{
	struct qstr dir = QSTR_INIT(dir_name, strlen(dir_name));
	return d_hash_and_lookup(sb->s_root, &dir);
}