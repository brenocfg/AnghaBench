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
 int /*<<< orphan*/  gdPutC (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gdBMPPutInt(gdIOCtx *out, int w)
{
	/* Byte order is little-endian */
	gdPutC(w & 0xFF, out);
	gdPutC((w >> 8) & 0xFF, out);
	gdPutC((w >> 16) & 0xFF, out);
	gdPutC((w >> 24) & 0xFF, out);
	return 0;
}