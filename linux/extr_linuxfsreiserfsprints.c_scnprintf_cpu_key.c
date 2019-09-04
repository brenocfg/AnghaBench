#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;
struct cpu_key {TYPE_1__ on_disk_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_type (struct cpu_key*) ; 
 int /*<<< orphan*/  reiserfs_cpu_offset (struct cpu_key*) ; 
 int scnprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static int scnprintf_cpu_key(char *buf, size_t size, struct cpu_key *key)
{
	if (key)
		return scnprintf(buf, size, "[%d %d %s %s]",
				 key->on_disk_key.k_dir_id,
				 key->on_disk_key.k_objectid,
				 reiserfs_cpu_offset(key), cpu_type(key));
	else
		return scnprintf(buf, size, "[NULL]");
}