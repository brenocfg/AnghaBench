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
struct fdarray {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fdarray__exit (struct fdarray*) ; 
 int /*<<< orphan*/  free (struct fdarray*) ; 

void fdarray__delete(struct fdarray *fda)
{
	fdarray__exit(fda);
	free(fda);
}