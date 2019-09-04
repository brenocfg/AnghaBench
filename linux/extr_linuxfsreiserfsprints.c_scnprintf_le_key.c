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
struct reiserfs_key {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_offset (struct reiserfs_key*) ; 
 int /*<<< orphan*/  le_type (struct reiserfs_key*) ; 
 int scnprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static int scnprintf_le_key(char *buf, size_t size, struct reiserfs_key *key)
{
	if (key)
		return scnprintf(buf, size, "[%d %d %s %s]",
				 le32_to_cpu(key->k_dir_id),
				 le32_to_cpu(key->k_objectid), le_offset(key),
				 le_type(key));
	else
		return scnprintf(buf, size, "[NULL]");
}