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
struct TYPE_2__ {char* data; size_t dsize_bytes; } ;
struct sclp_sd_file {int /*<<< orphan*/  data_mutex; TYPE_1__ data; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sclp_sd_file* to_sd_file (struct kobject*) ; 

__attribute__((used)) static ssize_t data_read(struct file *file, struct kobject *kobj,
			 struct bin_attribute *attr, char *buffer,
			 loff_t off, size_t size)
{
	struct sclp_sd_file *sd_file = to_sd_file(kobj);
	size_t data_size;
	char *data;

	mutex_lock(&sd_file->data_mutex);

	data = sd_file->data.data;
	data_size = sd_file->data.dsize_bytes;
	if (!data || off >= data_size) {
		size = 0;
	} else {
		if (off + size > data_size)
			size = data_size - off;
		memcpy(buffer, data + off, size);
	}

	mutex_unlock(&sd_file->data_mutex);

	return size;
}