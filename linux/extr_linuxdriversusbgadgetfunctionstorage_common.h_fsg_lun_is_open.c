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
struct fsg_lun {int /*<<< orphan*/ * filp; } ;

/* Variables and functions */

__attribute__((used)) static inline bool fsg_lun_is_open(struct fsg_lun *curlun)
{
	return curlun->filp != NULL;
}