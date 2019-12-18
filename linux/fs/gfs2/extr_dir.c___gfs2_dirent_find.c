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
struct qstr {scalar_t__ hash; scalar_t__ len; int /*<<< orphan*/  name; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_name_len; int /*<<< orphan*/  de_hash; } ;

/* Variables and functions */
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_dirent_sentinel (struct gfs2_dirent const*) ; 
 scalar_t__ memcmp (struct gfs2_dirent const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int __gfs2_dirent_find(const struct gfs2_dirent *dent,
				     const struct qstr *name, int ret)
{
	if (!gfs2_dirent_sentinel(dent) &&
	    be32_to_cpu(dent->de_hash) == name->hash &&
	    be16_to_cpu(dent->de_name_len) == name->len &&
	    memcmp(dent+1, name->name, name->len) == 0)
		return ret;
	return 0;
}