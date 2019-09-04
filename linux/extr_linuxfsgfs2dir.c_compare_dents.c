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
typedef  scalar_t__ u32 ;
struct gfs2_dirent {scalar_t__ de_cookie; int /*<<< orphan*/  de_name_len; } ;

/* Variables and functions */
 unsigned int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int memcmp (struct gfs2_dirent const*,struct gfs2_dirent const*,unsigned int) ; 

__attribute__((used)) static int compare_dents(const void *a, const void *b)
{
	const struct gfs2_dirent *dent_a, *dent_b;
	u32 hash_a, hash_b;
	int ret = 0;

	dent_a = *(const struct gfs2_dirent **)a;
	hash_a = dent_a->de_cookie;

	dent_b = *(const struct gfs2_dirent **)b;
	hash_b = dent_b->de_cookie;

	if (hash_a > hash_b)
		ret = 1;
	else if (hash_a < hash_b)
		ret = -1;
	else {
		unsigned int len_a = be16_to_cpu(dent_a->de_name_len);
		unsigned int len_b = be16_to_cpu(dent_b->de_name_len);

		if (len_a > len_b)
			ret = 1;
		else if (len_a < len_b)
			ret = -1;
		else
			ret = memcmp(dent_a + 1, dent_b + 1, len_a);
	}

	return ret;
}