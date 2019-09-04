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
struct qstr {unsigned int len; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_rec_len; int /*<<< orphan*/  de_name_len; } ;

/* Variables and functions */
 unsigned int GFS2_DIRENT_SIZE (unsigned int) ; 
 unsigned int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ gfs2_dirent_sentinel (struct gfs2_dirent const*) ; 

__attribute__((used)) static int gfs2_dirent_find_space(const struct gfs2_dirent *dent,
				  const struct qstr *name,
				  void *opaque)
{
	unsigned required = GFS2_DIRENT_SIZE(name->len);
	unsigned actual = GFS2_DIRENT_SIZE(be16_to_cpu(dent->de_name_len));
	unsigned totlen = be16_to_cpu(dent->de_rec_len);

	if (gfs2_dirent_sentinel(dent))
		actual = 0;
	if (totlen - actual >= required)
		return 1;
	return 0;
}