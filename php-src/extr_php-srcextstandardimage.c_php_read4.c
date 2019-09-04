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

__attribute__((used)) static unsigned int php_read4(php_stream * stream)
{
	unsigned char a[4];

	/* just return 0 if we hit the end-of-file */
	if ((php_stream_read(stream, (char*)a, sizeof(a))) != sizeof(a)) return 0;

	return (((unsigned int)a[0]) << 24)
	     + (((unsigned int)a[1]) << 16)
	     + (((unsigned int)a[2]) <<  8)
	     + (((unsigned int)a[3]));
}