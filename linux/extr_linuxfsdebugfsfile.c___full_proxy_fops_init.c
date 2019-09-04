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
struct file_operations {scalar_t__ unlocked_ioctl; scalar_t__ poll; scalar_t__ write; scalar_t__ read; scalar_t__ llseek; int /*<<< orphan*/  release; } ;

/* Variables and functions */
 scalar_t__ full_proxy_llseek ; 
 scalar_t__ full_proxy_poll ; 
 scalar_t__ full_proxy_read ; 
 int /*<<< orphan*/  full_proxy_release ; 
 scalar_t__ full_proxy_unlocked_ioctl ; 
 scalar_t__ full_proxy_write ; 

__attribute__((used)) static void __full_proxy_fops_init(struct file_operations *proxy_fops,
				const struct file_operations *real_fops)
{
	proxy_fops->release = full_proxy_release;
	if (real_fops->llseek)
		proxy_fops->llseek = full_proxy_llseek;
	if (real_fops->read)
		proxy_fops->read = full_proxy_read;
	if (real_fops->write)
		proxy_fops->write = full_proxy_write;
	if (real_fops->poll)
		proxy_fops->poll = full_proxy_poll;
	if (real_fops->unlocked_ioctl)
		proxy_fops->unlocked_ioctl = full_proxy_unlocked_ioctl;
}