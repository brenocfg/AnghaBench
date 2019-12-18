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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  optbuf ;
struct TYPE_2__ {char* format; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char ANSI_NULL ; 
 int _snprintf (char*,int,char*,char) ; 
 TYPE_1__* dhcp_options ; 
 int /*<<< orphan*/  error (char*,unsigned int) ; 
 scalar_t__ getLong (unsigned char*) ; 
 char getShort (unsigned char*) ; 
 scalar_t__ getULong (unsigned char*) ; 
 char getUShort (unsigned char*) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  isascii (unsigned char) ; 
 int /*<<< orphan*/  isprint (unsigned char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  warning (char*,...) ; 

char *
pretty_print_option(unsigned int code, unsigned char *data, int len,
    int emit_commas, int emit_quotes)
{
	static char optbuf[32768]; /* XXX */
	int hunksize = 0, numhunk = -1, numelem = 0;
	char fmtbuf[32], *op = optbuf;
	int i, j, k, opleft = sizeof(optbuf);
	unsigned char *dp = data;
	struct in_addr foo;
	char comma;

	/* Code should be between 0 and 255. */
	if (code > 255)
		error("pretty_print_option: bad code %d", code);

	if (emit_commas)
		comma = ',';
	else
		comma = ' ';

	/* Figure out the size of the data. */
	for (i = 0; dhcp_options[code].format[i]; i++) {
		if (!numhunk) {
			warning("%s: Excess information in format string: %s",
			    dhcp_options[code].name,
			    &(dhcp_options[code].format[i]));
			break;
		}
		numelem++;
		fmtbuf[i] = dhcp_options[code].format[i];
		switch (dhcp_options[code].format[i]) {
		case 'A':
			--numelem;
			fmtbuf[i] = 0;
			numhunk = 0;
			break;
		case 'X':
			for (k = 0; k < len; k++)
				if (!isascii(data[k]) ||
				    !isprint(data[k]))
					break;
			if (k == len) {
				fmtbuf[i] = 't';
				numhunk = -2;
			} else {
				fmtbuf[i] = 'x';
				hunksize++;
				comma = ':';
				numhunk = 0;
			}
			fmtbuf[i + 1] = 0;
			break;
		case 't':
			fmtbuf[i] = 't';
			fmtbuf[i + 1] = 0;
			numhunk = -2;
			break;
		case 'I':
		case 'l':
		case 'L':
			hunksize += 4;
			break;
		case 's':
		case 'S':
			hunksize += 2;
			break;
		case 'b':
		case 'B':
		case 'f':
			hunksize++;
			break;
		case 'e':
			break;
		default:
			warning("%s: garbage in format string: %s",
			    dhcp_options[code].name,
			    &(dhcp_options[code].format[i]));
			break;
		}
	}

	/* Check for too few bytes... */
	if (hunksize > len) {
		warning("%s: expecting at least %d bytes; got %d",
		    dhcp_options[code].name, hunksize, len);
		return ("<error>");
	}
	/* Check for too many bytes... */
	if (numhunk == -1 && hunksize < len)
		warning("%s: %d extra bytes",
		    dhcp_options[code].name, len - hunksize);

	/* If this is an array, compute its size. */
	if (!numhunk)
		numhunk = len / hunksize;
	/* See if we got an exact number of hunks. */
	if (numhunk > 0 && numhunk * hunksize < len)
		warning("%s: %d extra bytes at end of array",
		    dhcp_options[code].name, len - numhunk * hunksize);

	/* A one-hunk array prints the same as a single hunk. */
	if (numhunk < 0)
		numhunk = 1;

	/* Cycle through the array (or hunk) printing the data. */
	for (i = 0; i < numhunk; i++) {
		for (j = 0; j < numelem; j++) {
			int opcount;
			switch (fmtbuf[j]) {
			case 't':
				if (emit_quotes) {
					*op++ = '"';
					opleft--;
				}
				for (; dp < data + len; dp++) {
					if (!isascii(*dp) ||
					    !isprint(*dp)) {
						if (dp + 1 != data + len ||
						    *dp != 0) {
							_snprintf(op, opleft,
							    "\\%03o", *dp);
							op += 4;
							opleft -= 4;
						}
					} else if (*dp == '"' ||
					    *dp == '\'' ||
					    *dp == '$' ||
					    *dp == '`' ||
					    *dp == '\\') {
						*op++ = '\\';
						*op++ = *dp;
						opleft -= 2;
					} else {
						*op++ = *dp;
						opleft--;
					}
				}
				if (emit_quotes) {
					*op++ = '"';
					opleft--;
				}

				*op = 0;
				break;
			case 'I':
				foo.s_addr = htonl(getULong(dp));
				strncpy(op, inet_ntoa(foo), opleft - 1);
				op[opleft - 1] = ANSI_NULL;
				opcount = strlen(op);
				if (opcount >= opleft)
					goto toobig;
				opleft -= opcount;
				dp += 4;
				break;
			case 'l':
				opcount = _snprintf(op, opleft, "%ld",
				    (long)getLong(dp));
				if (opcount >= opleft || opcount == -1)
					goto toobig;
				opleft -= opcount;
				dp += 4;
				break;
			case 'L':
				opcount = _snprintf(op, opleft, "%ld",
				    (unsigned long)getULong(dp));
				if (opcount >= opleft || opcount == -1)
					goto toobig;
				opleft -= opcount;
				dp += 4;
				break;
			case 's':
				opcount = _snprintf(op, opleft, "%d",
				    getShort(dp));
				if (opcount >= opleft || opcount == -1)
					goto toobig;
				opleft -= opcount;
				dp += 2;
				break;
			case 'S':
				opcount = _snprintf(op, opleft, "%d",
				    getUShort(dp));
				if (opcount >= opleft || opcount == -1)
					goto toobig;
				opleft -= opcount;
				dp += 2;
				break;
			case 'b':
				opcount = _snprintf(op, opleft, "%d",
				    *(char *)dp++);
				if (opcount >= opleft || opcount == -1)
					goto toobig;
				opleft -= opcount;
				break;
			case 'B':
				opcount = _snprintf(op, opleft, "%d", *dp++);
				if (opcount >= opleft || opcount == -1)
					goto toobig;
				opleft -= opcount;
				break;
			case 'x':
				opcount = _snprintf(op, opleft, "%x", *dp++);
				if (opcount >= opleft || opcount == -1)
					goto toobig;
				opleft -= opcount;
				break;
			case 'f':
				opcount = (size_t) strncpy(op, *dp++ ? "true" : "false", opleft - 1);
				op[opleft - 1] = ANSI_NULL;
				if (opcount >= opleft)
					goto toobig;
				opleft -= opcount;
				break;
			default:
				warning("Unexpected format code %c", fmtbuf[j]);
			}
			op += strlen(op);
			opleft -= strlen(op);
			if (opleft < 1)
				goto toobig;
			if (j + 1 < numelem && comma != ':') {
				*op++ = ' ';
				opleft--;
			}
		}
		if (i + 1 < numhunk) {
			*op++ = comma;
			opleft--;
		}
		if (opleft < 1)
			goto toobig;

	}
	return (optbuf);
 toobig:
	warning("dhcp option too large");
	return ("<error>");
}