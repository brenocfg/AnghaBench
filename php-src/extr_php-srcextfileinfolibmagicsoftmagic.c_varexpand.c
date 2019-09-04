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
struct TYPE_2__ {int st_mode; } ;
struct buffer {TYPE_1__ st; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int
varexpand(char *buf, size_t len, const struct buffer *b, const char *str)
{
	const char *ptr, *sptr, *e, *t, *ee, *et;
	size_t l;

	for (sptr = str; (ptr = strstr(sptr, "${")) != NULL;) {
		l = (size_t)(ptr - sptr);
		if (l >= len)
			return -1;
		memcpy(buf, sptr, l);
		buf += l;
		len -= l;
		ptr += 2;
		if (!*ptr || ptr[1] != '?')
			return -1;
		for (et = t = ptr + 2; *et && *et != ':'; et++)
			continue;
		if (*et != ':')
			return -1;
		for (ee = e = et + 1; *ee && *ee != '}'; ee++)
			continue;
		if (*ee != '}')
			return -1;
		switch (*ptr) {
		case 'x':
			if (b->st.st_mode & 0111) {
				ptr = t;
				l = et - t;
			} else {
				ptr = e;
				l = ee - e;
			}
			break;
		default:
			return -1;
		}
		if (l >= len)
			return -1;
		memcpy(buf, ptr, l);
		buf += l;
		len -= l;
		sptr = ee + 1;
	}

	l = strlen(sptr);
	if (l >= len)
		return -1;

	memcpy(buf, sptr, l);
	buf[l] = '\0';
	return 0;
}