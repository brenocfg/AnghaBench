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
struct fat_mount_options {char name_check; int /*<<< orphan*/  nocase; scalar_t__ dotsOK; } ;

/* Variables and functions */
 int EINVAL ; 
 int MSDOS_NAME ; 
 int /*<<< orphan*/  bad_chars ; 
 int /*<<< orphan*/  bad_if_strict ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int msdos_format_name(const unsigned char *name, int len,
			     unsigned char *res, struct fat_mount_options *opts)
	/*
	 * name is the proposed name, len is its length, res is
	 * the resulting name, opts->name_check is either (r)elaxed,
	 * (n)ormal or (s)trict, opts->dotsOK allows dots at the
	 * beginning of name (for hidden files)
	 */
{
	unsigned char *walk;
	unsigned char c;
	int space;

	if (name[0] == '.') {	/* dotfile because . and .. already done */
		if (opts->dotsOK) {
			/* Get rid of dot - test for it elsewhere */
			name++;
			len--;
		} else
			return -EINVAL;
	}
	/*
	 * disallow names that _really_ start with a dot
	 */
	space = 1;
	c = 0;
	for (walk = res; len && walk - res < 8; walk++) {
		c = *name++;
		len--;
		if (opts->name_check != 'r' && strchr(bad_chars, c))
			return -EINVAL;
		if (opts->name_check == 's' && strchr(bad_if_strict, c))
			return -EINVAL;
		if (c >= 'A' && c <= 'Z' && opts->name_check == 's')
			return -EINVAL;
		if (c < ' ' || c == ':' || c == '\\')
			return -EINVAL;
	/*
	 * 0xE5 is legal as a first character, but we must substitute
	 * 0x05 because 0xE5 marks deleted files.  Yes, DOS really
	 * does this.
	 * It seems that Microsoft hacked DOS to support non-US
	 * characters after the 0xE5 character was already in use to
	 * mark deleted files.
	 */
		if ((res == walk) && (c == 0xE5))
			c = 0x05;
		if (c == '.')
			break;
		space = (c == ' ');
		*walk = (!opts->nocase && c >= 'a' && c <= 'z') ? c - 32 : c;
	}
	if (space)
		return -EINVAL;
	if (opts->name_check == 's' && len && c != '.') {
		c = *name++;
		len--;
		if (c != '.')
			return -EINVAL;
	}
	while (c != '.' && len--)
		c = *name++;
	if (c == '.') {
		while (walk - res < 8)
			*walk++ = ' ';
		while (len > 0 && walk - res < MSDOS_NAME) {
			c = *name++;
			len--;
			if (opts->name_check != 'r' && strchr(bad_chars, c))
				return -EINVAL;
			if (opts->name_check == 's' &&
			    strchr(bad_if_strict, c))
				return -EINVAL;
			if (c < ' ' || c == ':' || c == '\\')
				return -EINVAL;
			if (c == '.') {
				if (opts->name_check == 's')
					return -EINVAL;
				break;
			}
			if (c >= 'A' && c <= 'Z' && opts->name_check == 's')
				return -EINVAL;
			space = c == ' ';
			if (!opts->nocase && c >= 'a' && c <= 'z')
				*walk++ = c - 32;
			else
				*walk++ = c;
		}
		if (space)
			return -EINVAL;
		if (opts->name_check == 's' && len)
			return -EINVAL;
	}
	while (walk - res < MSDOS_NAME)
		*walk++ = ' ';

	return 0;
}