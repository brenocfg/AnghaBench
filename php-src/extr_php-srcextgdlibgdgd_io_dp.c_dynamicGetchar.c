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
typedef  int /*<<< orphan*/  gdIOCtxPtr ;

/* Variables and functions */
 int EOF ; 
 int dynamicGetbuf (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int dynamicGetchar (gdIOCtxPtr ctx)
{
	unsigned char b;
	int rv;

	rv = dynamicGetbuf (ctx, &b, 1);
	if (rv != 1) {
		return EOF;
	} else {
		return b; 		/* (b & 0xff); */
	}
}