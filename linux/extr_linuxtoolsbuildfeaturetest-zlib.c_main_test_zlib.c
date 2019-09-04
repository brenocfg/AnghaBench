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
typedef  int /*<<< orphan*/  z_stream ;

/* Variables and functions */
 int /*<<< orphan*/  inflateInit (int /*<<< orphan*/ *) ; 

int main(void)
{
	z_stream zs;

	inflateInit(&zs);
	return 0;
}