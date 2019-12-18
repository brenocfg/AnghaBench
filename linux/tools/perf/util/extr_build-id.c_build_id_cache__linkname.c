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

/* Variables and functions */
 int asnprintf (char**,size_t,char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  buildid_dir ; 

char *build_id_cache__linkname(const char *sbuild_id, char *bf, size_t size)
{
	char *tmp = bf;
	int ret = asnprintf(&bf, size, "%s/.build-id/%.2s/%s", buildid_dir,
			    sbuild_id, sbuild_id + 2);
	if (ret < 0 || (tmp && size < (unsigned int)ret))
		return NULL;
	return bf;
}