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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,unsigned int,int,...) ; 
 int /*<<< orphan*/  err (char*,unsigned int,...) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ isxdigit (char) ; 
 scalar_t__ new_class (char*,unsigned int) ; 
 scalar_t__ new_product (char*,int,unsigned int) ; 
 scalar_t__ new_protocol (char*,int,int,unsigned int) ; 
 scalar_t__ new_subclass (char*,int,unsigned int) ; 
 scalar_t__ new_vendor (char*,unsigned int) ; 
 char* strchr (char*,char) ; 
 unsigned int strtoul (char*,char**,int) ; 

__attribute__((used)) static void parse(FILE *f)
{
	char buf[512], *cp;
	unsigned int linectr = 0;
	int lastvendor = -1;
	int lastclass = -1;
	int lastsubclass = -1;
	int lasthut = -1;
	int lastlang = -1;
	unsigned int u;

	while (fgets(buf, sizeof(buf), f)) {
		linectr++;
		/* remove line ends */
		cp = strchr(buf, '\r');
		if (cp)
			*cp = 0;
		cp = strchr(buf, '\n');
		if (cp)
			*cp = 0;
		if (buf[0] == '#' || !buf[0])
			continue;
		cp = buf;
		if (buf[0] == 'P' && buf[1] == 'H' && buf[2] == 'Y' &&
		    buf[3] == 'S' && buf[4] == 'D' &&
		    buf[5] == 'E' && buf[6] == 'S' && /*isspace(buf[7])*/
		    buf[7] == ' ') {
			continue;
		}
		if (buf[0] == 'P' && buf[1] == 'H' &&
		    buf[2] == 'Y' && /*isspace(buf[3])*/ buf[3] == ' ') {
			continue;
		}
		if (buf[0] == 'B' && buf[1] == 'I' && buf[2] == 'A' &&
		    buf[3] == 'S' && /*isspace(buf[4])*/ buf[4] == ' ') {
			continue;
		}
		if (buf[0] == 'L' && /*isspace(buf[1])*/ buf[1] == ' ') {
			lasthut = lastclass = lastvendor = lastsubclass = -1;
			/*
			 * set 1 as pseudo-id to indicate that the parser is
			 * in a `L' section.
			 */
			lastlang = 1;
			continue;
		}
		if (buf[0] == 'C' && /*isspace(buf[1])*/ buf[1] == ' ') {
			/* class spec */
			cp = buf+2;
			while (isspace(*cp))
				cp++;
			if (!isxdigit(*cp)) {
				err("Invalid class spec at line %u", linectr);
				continue;
			}
			u = strtoul(cp, &cp, 16);
			while (isspace(*cp))
				cp++;
			if (!*cp) {
				err("Invalid class spec at line %u", linectr);
				continue;
			}
			if (new_class(cp, u))
				err("Duplicate class spec at line %u class %04x %s",
				    linectr, u, cp);
			dbg("line %5u class %02x %s", linectr, u, cp);
			lasthut = lastlang = lastvendor = lastsubclass = -1;
			lastclass = u;
			continue;
		}
		if (buf[0] == 'A' && buf[1] == 'T' && isspace(buf[2])) {
			/* audio terminal type spec */
			continue;
		}
		if (buf[0] == 'H' && buf[1] == 'C' && buf[2] == 'C'
		    && isspace(buf[3])) {
			/* HID Descriptor bCountryCode */
			continue;
		}
		if (isxdigit(*cp)) {
			/* vendor */
			u = strtoul(cp, &cp, 16);
			while (isspace(*cp))
				cp++;
			if (!*cp) {
				err("Invalid vendor spec at line %u", linectr);
				continue;
			}
			if (new_vendor(cp, u))
				err("Duplicate vendor spec at line %u vendor %04x %s",
				    linectr, u, cp);
			dbg("line %5u vendor %04x %s", linectr, u, cp);
			lastvendor = u;
			lasthut = lastlang = lastclass = lastsubclass = -1;
			continue;
		}
		if (buf[0] == '\t' && isxdigit(buf[1])) {
			/* product or subclass spec */
			u = strtoul(buf+1, &cp, 16);
			while (isspace(*cp))
				cp++;
			if (!*cp) {
				err("Invalid product/subclass spec at line %u",
				    linectr);
				continue;
			}
			if (lastvendor != -1) {
				if (new_product(cp, lastvendor, u))
					err("Duplicate product spec at line %u product %04x:%04x %s",
					    linectr, lastvendor, u, cp);
				dbg("line %5u product %04x:%04x %s", linectr,
				    lastvendor, u, cp);
				continue;
			}
			if (lastclass != -1) {
				if (new_subclass(cp, lastclass, u))
					err("Duplicate subclass spec at line %u class %02x:%02x %s",
					    linectr, lastclass, u, cp);
				dbg("line %5u subclass %02x:%02x %s", linectr,
				    lastclass, u, cp);
				lastsubclass = u;
				continue;
			}
			if (lasthut != -1) {
				/* do not store hut */
				continue;
			}
			if (lastlang != -1) {
				/* do not store langid */
				continue;
			}
			err("Product/Subclass spec without prior Vendor/Class spec at line %u",
			    linectr);
			continue;
		}
		if (buf[0] == '\t' && buf[1] == '\t' && isxdigit(buf[2])) {
			/* protocol spec */
			u = strtoul(buf+2, &cp, 16);
			while (isspace(*cp))
				cp++;
			if (!*cp) {
				err("Invalid protocol spec at line %u",
				    linectr);
				continue;
			}
			if (lastclass != -1 && lastsubclass != -1) {
				if (new_protocol(cp, lastclass, lastsubclass,
						 u))
					err("Duplicate protocol spec at line %u class %02x:%02x:%02x %s",
					    linectr, lastclass, lastsubclass,
					    u, cp);
				dbg("line %5u protocol %02x:%02x:%02x %s",
				    linectr, lastclass, lastsubclass, u, cp);
				continue;
			}
			err("Protocol spec without prior Class and Subclass spec at line %u",
			    linectr);
			continue;
		}
		if (buf[0] == 'H' && buf[1] == 'I' &&
		    buf[2] == 'D' && /*isspace(buf[3])*/ buf[3] == ' ') {
			continue;
		}
		if (buf[0] == 'H' && buf[1] == 'U' &&
		    buf[2] == 'T' && /*isspace(buf[3])*/ buf[3] == ' ') {
			lastlang = lastclass = lastvendor = lastsubclass = -1;
			/*
			 * set 1 as pseudo-id to indicate that the parser is
			 * in a `HUT' section.
			 */
			lasthut = 1;
			continue;
		}
		if (buf[0] == 'R' && buf[1] == ' ')
			continue;

		if (buf[0] == 'V' && buf[1] == 'T')
			continue;

		err("Unknown line at line %u", linectr);
	}
}