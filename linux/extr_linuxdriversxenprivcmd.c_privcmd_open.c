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
struct privcmd_data {int /*<<< orphan*/  domid; } ;
struct inode {int dummy; } ;
struct file {struct privcmd_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_INVALID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct privcmd_data* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int privcmd_open(struct inode *ino, struct file *file)
{
	struct privcmd_data *data = kzalloc(sizeof(*data), GFP_KERNEL);

	if (!data)
		return -ENOMEM;

	/* DOMID_INVALID implies no restriction */
	data->domid = DOMID_INVALID;

	file->private_data = data;
	return 0;
}