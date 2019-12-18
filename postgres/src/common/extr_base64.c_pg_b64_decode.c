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
typedef  int uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int* b64lookup ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

int
pg_b64_decode(const char *src, int len, char *dst, int dstlen)
{
	const char *srcend = src + len,
			   *s = src;
	char	   *p = dst;
	char		c;
	int			b = 0;
	uint32		buf = 0;
	int			pos = 0,
				end = 0;

	while (s < srcend)
	{
		c = *s++;

		/* Leave if a whitespace is found */
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
			goto error;

		if (c == '=')
		{
			/* end sequence */
			if (!end)
			{
				if (pos == 2)
					end = 1;
				else if (pos == 3)
					end = 2;
				else
				{
					/*
					 * Unexpected "=" character found while decoding base64
					 * sequence.
					 */
					goto error;
				}
			}
			b = 0;
		}
		else
		{
			b = -1;
			if (c > 0 && c < 127)
				b = b64lookup[(unsigned char) c];
			if (b < 0)
			{
				/* invalid symbol found */
				goto error;
			}
		}
		/* add it to buffer */
		buf = (buf << 6) + b;
		pos++;
		if (pos == 4)
		{
			/*
			 * Leave if there is an overflow in the area allocated for the
			 * decoded string.
			 */
			if ((p - dst + 1) > dstlen)
				goto error;
			*p++ = (buf >> 16) & 255;

			if (end == 0 || end > 1)
			{
				/* overflow check */
				if ((p - dst + 1) > dstlen)
					goto error;
				*p++ = (buf >> 8) & 255;
			}
			if (end == 0 || end > 2)
			{
				/* overflow check */
				if ((p - dst + 1) > dstlen)
					goto error;
				*p++ = buf & 255;
			}
			buf = 0;
			pos = 0;
		}
	}

	if (pos != 0)
	{
		/*
		 * base64 end sequence is invalid.  Input data is missing padding, is
		 * truncated or is otherwise corrupted.
		 */
		goto error;
	}

	Assert((p - dst) <= dstlen);
	return p - dst;

error:
	memset(dst, 0, dstlen);
	return -1;
}