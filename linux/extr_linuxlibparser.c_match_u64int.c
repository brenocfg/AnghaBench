#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {size_t to; size_t from; } ;
typedef  TYPE_1__ substring_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int kstrtoull (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,size_t,size_t) ; 

__attribute__((used)) static int match_u64int(substring_t *s, u64 *result, int base)
{
	char *buf;
	int ret;
	u64 val;
	size_t len = s->to - s->from;

	buf = kmalloc(len + 1, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	memcpy(buf, s->from, len);
	buf[len] = '\0';

	ret = kstrtoull(buf, base, &val);
	if (!ret)
		*result = val;
	kfree(buf);
	return ret;
}