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
typedef  int /*<<< orphan*/  uchar ;
typedef  int /*<<< orphan*/  block_dev_desc_t ;

/* Variables and functions */
 int CONFIG_ENV_SIZE ; 
 int EXT4_ENV_DEVICE ; 
 char* EXT4_ENV_FILE ; 
 char* EXT4_ENV_INTERFACE ; 
 int EXT4_ENV_PART ; 
 int /*<<< orphan*/  env_import (char*,int) ; 
 int ext4_read_file (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ext4_register_device (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ext4fs_close () ; 
 int /*<<< orphan*/ * get_dev (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  set_default_env (int /*<<< orphan*/ *) ; 

void env_relocate_spec(void)
{
	char buf[CONFIG_ENV_SIZE];
	block_dev_desc_t *dev_desc = NULL;
	int dev = EXT4_ENV_DEVICE;
	int part = EXT4_ENV_PART;
	int err;

	dev_desc = get_dev(EXT4_ENV_INTERFACE, dev);
	if (dev_desc == NULL) {
		printf("Failed to find %s%d\n",
			EXT4_ENV_INTERFACE, dev);
		set_default_env(NULL);
		return;
	}

	err = ext4_register_device(dev_desc, part);
	if (err) {
		printf("Failed to register %s%d:%d\n",
			EXT4_ENV_INTERFACE, dev, part);
		set_default_env(NULL);
		return;
	}

	err = ext4_read_file(EXT4_ENV_FILE, (uchar *)&buf, 0, CONFIG_ENV_SIZE);
	ext4fs_close();

	if (err == -1) {
		printf("\n** Unable to read \"%s\" from %s%d:%d **\n",
			EXT4_ENV_FILE, EXT4_ENV_INTERFACE, dev, part);
		set_default_env(NULL);
		return;
	}

	env_import(buf, 1);
}