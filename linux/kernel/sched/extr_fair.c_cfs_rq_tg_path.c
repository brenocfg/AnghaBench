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
struct cfs_rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static inline void cfs_rq_tg_path(struct cfs_rq *cfs_rq, char *path, int len)
{
	if (path)
		strlcpy(path, "(null)", len);
}