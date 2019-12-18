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
typedef  char uint8 ;
typedef  int Size ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int PXE_PGP_CORRUPT_ARMOR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int find_header (char const*,char const*,char const**,int) ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* palloc (int) ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,char*) ; 

int
pgp_extract_armor_headers(const uint8 *src, unsigned len,
						  int *nheaders, char ***keys, char ***values)
{
	const uint8 *data_end = src + len;
	const uint8 *p;
	const uint8 *base64_start;
	const uint8 *armor_start;
	const uint8 *armor_end;
	Size		armor_len;
	char	   *line;
	char	   *nextline;
	char	   *eol,
			   *colon;
	int			hlen;
	char	   *buf;
	int			hdrlines;
	int			n;

	/* armor start */
	hlen = find_header(src, data_end, &armor_start, 0);
	if (hlen <= 0)
		return PXE_PGP_CORRUPT_ARMOR;
	armor_start += hlen;

	/* armor end */
	hlen = find_header(armor_start, data_end, &armor_end, 1);
	if (hlen <= 0)
		return PXE_PGP_CORRUPT_ARMOR;

	/* Count the number of armor header lines. */
	hdrlines = 0;
	p = armor_start;
	while (p < armor_end && *p != '\n' && *p != '\r')
	{
		p = memchr(p, '\n', armor_end - p);
		if (!p)
			return PXE_PGP_CORRUPT_ARMOR;

		/* step to start of next line */
		p++;
		hdrlines++;
	}
	base64_start = p;

	/*
	 * Make a modifiable copy of the part of the input that contains the
	 * headers. The returned key/value pointers will point inside the buffer.
	 */
	armor_len = base64_start - armor_start;
	buf = palloc(armor_len + 1);
	memcpy(buf, armor_start, armor_len);
	buf[armor_len] = '\0';

	/* Allocate return arrays */
	*keys = (char **) palloc(hdrlines * sizeof(char *));
	*values = (char **) palloc(hdrlines * sizeof(char *));

	/*
	 * Split the header lines at newlines and ": " separators, and collect
	 * pointers to the keys and values in the return arrays.
	 */
	n = 0;
	line = buf;
	for (;;)
	{
		/* find end of line */
		eol = strchr(line, '\n');
		if (!eol)
			break;
		nextline = eol + 1;
		/* if the line ends in CR + LF, strip the CR */
		if (eol > line && *(eol - 1) == '\r')
			eol--;
		*eol = '\0';

		/* find colon+space separating the key and value */
		colon = strstr(line, ": ");
		if (!colon)
			return PXE_PGP_CORRUPT_ARMOR;
		*colon = '\0';

		/* shouldn't happen, we counted the number of lines beforehand */
		if (n >= hdrlines)
			elog(ERROR, "unexpected number of armor header lines");

		(*keys)[n] = line;
		(*values)[n] = colon + 2;
		n++;

		/* step to start of next line */
		line = nextline;
	}

	if (n != hdrlines)
		elog(ERROR, "unexpected number of armor header lines");

	*nheaders = n;
	return 0;
}