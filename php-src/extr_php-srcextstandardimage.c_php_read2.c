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
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int php_stream_read (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static unsigned short php_read2(php_stream * stream)
{
	unsigned char a[2];

	/* return 0 if we couldn't read enough data */
	if((php_stream_read(stream, (char *) a, sizeof(a))) < sizeof(a)) return 0;

	return (((unsigned short)a[0]) << 8) + ((unsigned short)a[1]);
}