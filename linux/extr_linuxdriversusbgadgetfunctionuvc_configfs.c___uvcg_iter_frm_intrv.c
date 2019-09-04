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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int __uvcg_iter_frm_intrv(const char *page, size_t len,
				 int (*fun)(char *, void *), void *priv)
{
	/* sign, base 2 representation, newline, terminator */
	char buf[1 + sizeof(u32) * 8 + 1 + 1];
	const char *pg = page;
	int i, ret;

	if (!fun)
		return -EINVAL;

	while (pg - page < len) {
		i = 0;
		while (i < sizeof(buf) && (pg - page < len) &&
				*pg != '\0' && *pg != '\n')
			buf[i++] = *pg++;
		if (i == sizeof(buf))
			return -EINVAL;
		while ((pg - page < len) && (*pg == '\0' || *pg == '\n'))
			++pg;
		buf[i] = '\0';
		ret = fun(buf, priv);
		if (ret)
			return ret;
	}

	return 0;
}