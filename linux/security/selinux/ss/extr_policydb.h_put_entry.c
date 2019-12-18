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
struct policy_file {size_t data; size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t,void const*,size_t) ; 

__attribute__((used)) static inline int put_entry(const void *buf, size_t bytes, int num, struct policy_file *fp)
{
	size_t len = bytes * num;

	memcpy(fp->data, buf, len);
	fp->data += len;
	fp->len -= len;

	return 0;
}