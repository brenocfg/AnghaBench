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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/  const*,char const,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char const*,int) ; 

__attribute__((used)) static const uint8 *
find_str(const uint8 *data, const uint8 *data_end, const char *str, int strlen)
{
	const uint8 *p = data;

	if (!strlen)
		return NULL;
	if (data_end - data < strlen)
		return NULL;
	while (p < data_end)
	{
		p = memchr(p, str[0], data_end - p);
		if (p == NULL)
			return NULL;
		if (p + strlen > data_end)
			return NULL;
		if (memcmp(p, str, strlen) == 0)
			return p;
		p++;
	}
	return NULL;
}