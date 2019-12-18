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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kstrndup (char const*,int,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static inline char *get_dfs_root(const char *path)
{
	char *s, *npath;

	s = strchr(path + 1, '\\');
	if (!s)
		return ERR_PTR(-EINVAL);

	s = strchr(s + 1, '\\');
	if (!s)
		return ERR_PTR(-EINVAL);

	npath = kstrndup(path, s - path, GFP_KERNEL);
	if (!npath)
		return ERR_PTR(-ENOMEM);

	return npath;
}