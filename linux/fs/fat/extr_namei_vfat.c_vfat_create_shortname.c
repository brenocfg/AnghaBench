#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct shortname_info {scalar_t__ lower; scalar_t__ upper; scalar_t__ valid; } ;
struct nls_table {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct fat_mount_options {int shortname; scalar_t__ numtail; } ;
typedef  int /*<<< orphan*/  charbuf ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {struct fat_mount_options options; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned char CASE_LOWER_BASE ; 
 unsigned char CASE_LOWER_EXT ; 
 unsigned char DELETED_FLAG ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_SHORTNAME_INFO (struct shortname_info*) ; 
 int /*<<< orphan*/  MSDOS_NAME ; 
 TYPE_1__* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int NLS_MAX_CHARSET_SIZE ; 
 int VFAT_SFN_CREATE_WIN95 ; 
 int VFAT_SFN_CREATE_WINNT ; 
 int jiffies ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (unsigned char*,int,char*,int) ; 
 int to_shortname_char (struct nls_table*,unsigned char*,int,int*,struct shortname_info*) ; 
 scalar_t__ vfat_find_form (struct inode*,unsigned char*) ; 
 int /*<<< orphan*/  vfat_skip_char (int) ; 

__attribute__((used)) static int vfat_create_shortname(struct inode *dir, struct nls_table *nls,
				 wchar_t *uname, int ulen,
				 unsigned char *name_res, unsigned char *lcase)
{
	struct fat_mount_options *opts = &MSDOS_SB(dir->i_sb)->options;
	wchar_t *ip, *ext_start, *end, *name_start;
	unsigned char base[9], ext[4], buf[5], *p;
	unsigned char charbuf[NLS_MAX_CHARSET_SIZE];
	int chl, chi;
	int sz = 0, extlen, baselen, i, numtail_baselen, numtail2_baselen;
	int is_shortname;
	struct shortname_info base_info, ext_info;

	is_shortname = 1;
	INIT_SHORTNAME_INFO(&base_info);
	INIT_SHORTNAME_INFO(&ext_info);

	/* Now, we need to create a shortname from the long name */
	ext_start = end = &uname[ulen];
	while (--ext_start >= uname) {
		if (*ext_start == 0x002E) {	/* is `.' */
			if (ext_start == end - 1) {
				sz = ulen;
				ext_start = NULL;
			}
			break;
		}
	}

	if (ext_start == uname - 1) {
		sz = ulen;
		ext_start = NULL;
	} else if (ext_start) {
		/*
		 * Names which start with a dot could be just
		 * an extension eg. "...test".  In this case Win95
		 * uses the extension as the name and sets no extension.
		 */
		name_start = &uname[0];
		while (name_start < ext_start) {
			if (!vfat_skip_char(*name_start))
				break;
			name_start++;
		}
		if (name_start != ext_start) {
			sz = ext_start - uname;
			ext_start++;
		} else {
			sz = ulen;
			ext_start = NULL;
		}
	}

	numtail_baselen = 6;
	numtail2_baselen = 2;
	for (baselen = i = 0, p = base, ip = uname; i < sz; i++, ip++) {
		chl = to_shortname_char(nls, charbuf, sizeof(charbuf),
					ip, &base_info);
		if (chl == 0)
			continue;

		if (baselen < 2 && (baselen + chl) > 2)
			numtail2_baselen = baselen;
		if (baselen < 6 && (baselen + chl) > 6)
			numtail_baselen = baselen;
		for (chi = 0; chi < chl; chi++) {
			*p++ = charbuf[chi];
			baselen++;
			if (baselen >= 8)
				break;
		}
		if (baselen >= 8) {
			if ((chi < chl - 1) || (ip + 1) - uname < sz)
				is_shortname = 0;
			break;
		}
	}
	if (baselen == 0) {
		return -EINVAL;
	}

	extlen = 0;
	if (ext_start) {
		for (p = ext, ip = ext_start; extlen < 3 && ip < end; ip++) {
			chl = to_shortname_char(nls, charbuf, sizeof(charbuf),
						ip, &ext_info);
			if (chl == 0)
				continue;

			if ((extlen + chl) > 3) {
				is_shortname = 0;
				break;
			}
			for (chi = 0; chi < chl; chi++) {
				*p++ = charbuf[chi];
				extlen++;
			}
			if (extlen >= 3) {
				if (ip + 1 != end)
					is_shortname = 0;
				break;
			}
		}
	}
	ext[extlen] = '\0';
	base[baselen] = '\0';

	/* Yes, it can happen. ".\xe5" would do it. */
	if (base[0] == DELETED_FLAG)
		base[0] = 0x05;

	/* OK, at this point we know that base is not longer than 8 symbols,
	 * ext is not longer than 3, base is nonempty, both don't contain
	 * any bad symbols (lowercase transformed to uppercase).
	 */

	memset(name_res, ' ', MSDOS_NAME);
	memcpy(name_res, base, baselen);
	memcpy(name_res + 8, ext, extlen);
	*lcase = 0;
	if (is_shortname && base_info.valid && ext_info.valid) {
		if (vfat_find_form(dir, name_res) == 0)
			return -EEXIST;

		if (opts->shortname & VFAT_SFN_CREATE_WIN95) {
			return (base_info.upper && ext_info.upper);
		} else if (opts->shortname & VFAT_SFN_CREATE_WINNT) {
			if ((base_info.upper || base_info.lower) &&
			    (ext_info.upper || ext_info.lower)) {
				if (!base_info.upper && base_info.lower)
					*lcase |= CASE_LOWER_BASE;
				if (!ext_info.upper && ext_info.lower)
					*lcase |= CASE_LOWER_EXT;
				return 1;
			}
			return 0;
		} else {
			BUG();
		}
	}

	if (opts->numtail == 0)
		if (vfat_find_form(dir, name_res) < 0)
			return 0;

	/*
	 * Try to find a unique extension.  This used to
	 * iterate through all possibilities sequentially,
	 * but that gave extremely bad performance.  Windows
	 * only tries a few cases before using random
	 * values for part of the base.
	 */

	if (baselen > 6) {
		baselen = numtail_baselen;
		name_res[7] = ' ';
	}
	name_res[baselen] = '~';
	for (i = 1; i < 10; i++) {
		name_res[baselen + 1] = i + '0';
		if (vfat_find_form(dir, name_res) < 0)
			return 0;
	}

	i = jiffies;
	sz = (jiffies >> 16) & 0x7;
	if (baselen > 2) {
		baselen = numtail2_baselen;
		name_res[7] = ' ';
	}
	name_res[baselen + 4] = '~';
	name_res[baselen + 5] = '1' + sz;
	while (1) {
		snprintf(buf, sizeof(buf), "%04X", i & 0xffff);
		memcpy(&name_res[baselen], buf, 4);
		if (vfat_find_form(dir, name_res) < 0)
			break;
		i -= 11;
	}
	return 0;
}