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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  isspace (char) ; 
 int kstrtoul (char*,int,unsigned long*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  swab16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hex2sprom(u16 *sprom, const char *dump, size_t len,
		     size_t sprom_size_words)
{
	char c, tmp[5] = { 0 };
	int err, cnt = 0;
	unsigned long parsed;

	/* Strip whitespace at the end. */
	while (len) {
		c = dump[len - 1];
		if (!isspace(c) && c != '\0')
			break;
		len--;
	}
	/* Length must match exactly. */
	if (len != sprom_size_words * 4)
		return -EINVAL;

	while (cnt < sprom_size_words) {
		memcpy(tmp, dump, 4);
		dump += 4;
		err = kstrtoul(tmp, 16, &parsed);
		if (err)
			return err;
		sprom[cnt++] = swab16((u16)parsed);
	}

	return 0;
}