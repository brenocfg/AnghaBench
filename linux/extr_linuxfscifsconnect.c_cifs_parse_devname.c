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
struct smb_vol {int /*<<< orphan*/  prepath; int /*<<< orphan*/  UNC; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  convert_delimiter (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrndup (char const*,int,int /*<<< orphan*/ ) ; 
 size_t strcspn (char*,char const*) ; 
 char* strpbrk (char const*,char const*) ; 
 size_t strspn (char const*,char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
cifs_parse_devname(const char *devname, struct smb_vol *vol)
{
	char *pos;
	const char *delims = "/\\";
	size_t len;

	if (unlikely(!devname || !*devname)) {
		cifs_dbg(VFS, "Device name not specified.\n");
		return -EINVAL;
	}

	/* make sure we have a valid UNC double delimiter prefix */
	len = strspn(devname, delims);
	if (len != 2)
		return -EINVAL;

	/* find delimiter between host and sharename */
	pos = strpbrk(devname + 2, delims);
	if (!pos)
		return -EINVAL;

	/* skip past delimiter */
	++pos;

	/* now go until next delimiter or end of string */
	len = strcspn(pos, delims);

	/* move "pos" up to delimiter or NULL */
	pos += len;
	vol->UNC = kstrndup(devname, pos - devname, GFP_KERNEL);
	if (!vol->UNC)
		return -ENOMEM;

	convert_delimiter(vol->UNC, '\\');

	/* skip any delimiter */
	if (*pos == '/' || *pos == '\\')
		pos++;

	/* If pos is NULL then no prepath */
	if (!*pos)
		return 0;

	vol->prepath = kstrdup(pos, GFP_KERNEL);
	if (!vol->prepath)
		return -ENOMEM;

	return 0;
}