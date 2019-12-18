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

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACTION_READ_ALL ; 
 int /*<<< orphan*/  CMD_ACTION_SIZE_BUFFER ; 
 int /*<<< orphan*/  free (char*) ; 
 int klogctl (int /*<<< orphan*/ ,char*,int) ; 
 char* malloc (int) ; 

__attribute__((used)) static char *get_klog_buff(unsigned int *klen)
{
	int ret, len;
	char *buff;

	len = klogctl(CMD_ACTION_SIZE_BUFFER, NULL, 0);
	if (len < 0)
		return NULL;

	buff = malloc(len);
	if (!buff)
		return NULL;

	ret = klogctl(CMD_ACTION_READ_ALL, buff, len);
	if (ret < 0) {
		free(buff);
		return NULL;
	}

	*klen = ret;
	return buff;
}