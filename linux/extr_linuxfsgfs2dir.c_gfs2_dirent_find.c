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
struct qstr {int dummy; } ;
struct gfs2_dirent {int dummy; } ;

/* Variables and functions */
 int __gfs2_dirent_find (struct gfs2_dirent const*,struct qstr const*,int) ; 

__attribute__((used)) static int gfs2_dirent_find(const struct gfs2_dirent *dent,
			    const struct qstr *name,
			    void *opaque)
{
	return __gfs2_dirent_find(dent, name, 1);
}