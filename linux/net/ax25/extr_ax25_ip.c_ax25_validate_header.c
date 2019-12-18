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
typedef  int /*<<< orphan*/  ax25_digi ;

/* Variables and functions */
 int ax25_addr_parse (char const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ax25_validate_header(const char *header, unsigned int len)
{
	ax25_digi digi;

	if (!len)
		return false;

	if (header[0])
		return true;

	return ax25_addr_parse(header + 1, len - 1, NULL, NULL, &digi, NULL,
			       NULL);
}