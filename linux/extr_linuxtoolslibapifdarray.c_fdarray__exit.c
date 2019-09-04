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
struct fdarray {int /*<<< orphan*/  priv; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  fdarray__init (struct fdarray*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void fdarray__exit(struct fdarray *fda)
{
	free(fda->entries);
	free(fda->priv);
	fdarray__init(fda, 0);
}