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
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  E_WARNING ; 
 unsigned int M_EOI ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 
 int php_stream_getc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int php_next_marker(php_stream * stream, int last_marker, int ff_read)
{
	int a=0, marker;

	/* get marker byte, swallowing possible padding                           */
	if (!ff_read) {
		size_t extraneous = 0;

		while ((marker = php_stream_getc(stream)) != 0xff) {
			if (marker == EOF) {
				return M_EOI;/* we hit EOF */
	}
			extraneous++;
	}
		if (extraneous) {
			php_error_docref(NULL, E_WARNING, "corrupt JPEG data: %zu extraneous bytes before marker", extraneous);
		}
	}
	a = 1;
	do {
		if ((marker = php_stream_getc(stream)) == EOF)
		{
			return M_EOI;/* we hit EOF */
		}
		a++;
	} while (marker == 0xff);
	if (a < 2)
	{
		return M_EOI; /* at least one 0xff is needed before marker code */
	}
	return (unsigned int)marker;
}