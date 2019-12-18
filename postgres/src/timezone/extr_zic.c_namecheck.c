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
 int /*<<< orphan*/  _ (char*) ; 
 int componentcheck (char const*,char const*,char const*) ; 
 scalar_t__ noise ; 
 scalar_t__ strchr (char const*,unsigned char) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*,unsigned char) ; 

__attribute__((used)) static bool
namecheck(const char *name)
{
	char const *cp;

	/* Benign characters in a portable file name.  */
	static char const benign[] =
	"-/_"
	"abcdefghijklmnopqrstuvwxyz"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	/*
	 * Non-control chars in the POSIX portable character set, excluding the
	 * benign characters.
	 */
	static char const printable_and_not_benign[] =
	" !\"#$%&'()*+,.0123456789:;<=>?@[\\]^`{|}~";

	char const *component = name;

	for (cp = name; *cp; cp++)
	{
		unsigned char c = *cp;

		if (noise && !strchr(benign, c))
		{
			warning((strchr(printable_and_not_benign, c)
					 ? _("file name '%s' contains byte '%c'")
					 : _("file name '%s' contains byte '\\%o'")),
					name, c);
		}
		if (c == '/')
		{
			if (!componentcheck(name, component, cp))
				return false;
			component = cp + 1;
		}
	}
	return componentcheck(name, component, cp);
}