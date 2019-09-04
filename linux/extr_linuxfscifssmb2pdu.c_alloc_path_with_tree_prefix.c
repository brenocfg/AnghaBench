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
typedef  int /*<<< orphan*/  wchar_t ;
struct nls_table {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  UniStrcat (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int UniStrnlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_strtoUTF16 (int /*<<< orphan*/ *,char const*,int,struct nls_table*) ; 
 int /*<<< orphan*/  const cpu_to_le16 (int) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nls_table* load_nls_default () ; 
 int roundup (int,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  unload_nls (struct nls_table*) ; 

__attribute__((used)) static int
alloc_path_with_tree_prefix(__le16 **out_path, int *out_size, int *out_len,
			    const char *treename, const __le16 *path)
{
	int treename_len, path_len;
	struct nls_table *cp;
	const __le16 sep[] = {cpu_to_le16('\\'), cpu_to_le16(0x0000)};

	/*
	 * skip leading "\\"
	 */
	treename_len = strlen(treename);
	if (treename_len < 2 || !(treename[0] == '\\' && treename[1] == '\\'))
		return -EINVAL;

	treename += 2;
	treename_len -= 2;

	path_len = UniStrnlen((wchar_t *)path, PATH_MAX);

	/*
	 * make room for one path separator between the treename and
	 * path
	 */
	*out_len = treename_len + 1 + path_len;

	/*
	 * final path needs to be null-terminated UTF16 with a
	 * size aligned to 8
	 */

	*out_size = roundup((*out_len+1)*2, 8);
	*out_path = kzalloc(*out_size, GFP_KERNEL);
	if (!*out_path)
		return -ENOMEM;

	cp = load_nls_default();
	cifs_strtoUTF16(*out_path, treename, treename_len, cp);
	UniStrcat(*out_path, sep);
	UniStrcat(*out_path, path);
	unload_nls(cp);

	return 0;
}