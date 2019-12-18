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
struct key {int dummy; } ;
struct file {struct afs_file* private_data; } ;
struct afs_file {struct key* key; } ;

/* Variables and functions */

__attribute__((used)) static inline struct key *afs_file_key(struct file *file)
{
	struct afs_file *af = file->private_data;

	return af->key;
}