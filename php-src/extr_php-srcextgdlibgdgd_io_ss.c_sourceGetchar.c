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
typedef  int /*<<< orphan*/  gdIOCtx ;

/* Variables and functions */
 int EOF ; 
 int sourceGetbuf (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static int sourceGetchar (gdIOCtx * ctx)
{
	int res;
	unsigned char buf;

	res = sourceGetbuf (ctx, &buf, 1);

	if (res == 1) {
		return buf;
	} else {
		return EOF;
	}
}