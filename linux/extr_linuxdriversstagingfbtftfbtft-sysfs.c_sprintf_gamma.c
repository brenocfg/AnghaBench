#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned int num_curves; unsigned int num_values; int /*<<< orphan*/  lock; } ;
struct fbtft_par {TYPE_1__ gamma; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
sprintf_gamma(struct fbtft_par *par, u32 *curves, char *buf)
{
	ssize_t len = 0;
	unsigned int i, j;

	mutex_lock(&par->gamma.lock);
	for (i = 0; i < par->gamma.num_curves; i++) {
		for (j = 0; j < par->gamma.num_values; j++)
			len += scnprintf(&buf[len], PAGE_SIZE,
			     "%04x ", curves[i * par->gamma.num_values + j]);
		buf[len - 1] = '\n';
	}
	mutex_unlock(&par->gamma.lock);

	return len;
}