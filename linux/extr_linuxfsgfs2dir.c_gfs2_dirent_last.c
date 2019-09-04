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
struct qstr {char* name; int len; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_rec_len; } ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_dirent_last(const struct gfs2_dirent *dent,
			    const struct qstr *name,
			    void *opaque)
{
	const char *start = name->name;
	const char *end = (const char *)dent + be16_to_cpu(dent->de_rec_len);
	if (name->len == (end - start))
		return 1;
	return 0;
}