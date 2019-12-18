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
 char* get_flog_buff (char const*,unsigned int*) ; 
 char* get_klog_buff (unsigned int*) ; 

__attribute__((used)) static char *get_log_buff(const char *file, unsigned int *klen)
{
	return file ? get_flog_buff(file, klen) : get_klog_buff(klen);
}