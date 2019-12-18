#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8 ;
struct TYPE_4__ {int len; scalar_t__ data; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 int PXE_PGP_CORRUPT_ARMOR ; 
 long crc24 (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  enlargeStringInfo (TYPE_1__*,int) ; 
 int find_header (char const*,char const*,char const**,int) ; 
 char* memchr (char const*,char,int) ; 
 scalar_t__ pg_base64_dec_len (int) ; 
 int pg_base64_decode (char const*,int,char*) ; 

int
pgp_armor_decode(const uint8 *src, int len, StringInfo dst)
{
	const uint8 *p = src;
	const uint8 *data_end = src + len;
	long		crc;
	const uint8 *base64_start,
			   *armor_end;
	const uint8 *base64_end = NULL;
	uint8		buf[4];
	int			hlen;
	int			blen;
	int			res = PXE_PGP_CORRUPT_ARMOR;

	/* armor start */
	hlen = find_header(src, data_end, &p, 0);
	if (hlen <= 0)
		goto out;
	p += hlen;

	/* armor end */
	hlen = find_header(p, data_end, &armor_end, 1);
	if (hlen <= 0)
		goto out;

	/* skip comments - find empty line */
	while (p < armor_end && *p != '\n' && *p != '\r')
	{
		p = memchr(p, '\n', armor_end - p);
		if (!p)
			goto out;

		/* step to start of next line */
		p++;
	}
	base64_start = p;

	/* find crc pos */
	for (p = armor_end; p >= base64_start; p--)
		if (*p == '=')
		{
			base64_end = p - 1;
			break;
		}
	if (base64_end == NULL)
		goto out;

	/* decode crc */
	if (pg_base64_decode(p + 1, 4, buf) != 3)
		goto out;
	crc = (((long) buf[0]) << 16) + (((long) buf[1]) << 8) + (long) buf[2];

	/* decode data */
	blen = (int) pg_base64_dec_len(len);
	enlargeStringInfo(dst, blen);
	res = pg_base64_decode(base64_start, base64_end - base64_start, (uint8 *) dst->data);
	if (res > blen)
		elog(FATAL, "overflow - decode estimate too small");
	if (res >= 0)
	{
		if (crc24((uint8 *) dst->data, res) == crc)
			dst->len += res;
		else
			res = PXE_PGP_CORRUPT_ARMOR;
	}
out:
	return res;
}