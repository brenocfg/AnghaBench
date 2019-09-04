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
struct xt_match {int matchsize; } ;

/* Variables and functions */
 int XT_ALIGN (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void match_compat_from_user(struct xt_match *m, void *in, void *out)
{
	int pad;

	memcpy(out, in, m->matchsize);
	pad = XT_ALIGN(m->matchsize) - m->matchsize;
	if (pad > 0)
		memset(out + m->matchsize, 0, pad);
}