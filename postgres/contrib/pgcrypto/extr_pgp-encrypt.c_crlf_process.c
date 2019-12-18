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
typedef  int /*<<< orphan*/  PushFilter ;

/* Variables and functions */
 char* memchr (char const*,char,int) ; 
 int pushf_write (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int
crlf_process(PushFilter *dst, void *priv, const uint8 *data, int len)
{
	const uint8 *data_end = data + len;
	const uint8 *p2,
			   *p1 = data;
	int			line_len;
	static const uint8 crlf[] = {'\r', '\n'};
	int			res = 0;

	while (p1 < data_end)
	{
		p2 = memchr(p1, '\n', data_end - p1);
		if (p2 == NULL)
			p2 = data_end;

		line_len = p2 - p1;

		/* write data */
		res = 0;
		if (line_len > 0)
		{
			res = pushf_write(dst, p1, line_len);
			if (res < 0)
				break;
			p1 += line_len;
		}

		/* write crlf */
		while (p1 < data_end && *p1 == '\n')
		{
			res = pushf_write(dst, crlf, 2);
			if (res < 0)
				break;
			p1++;
		}
	}
	return res;
}