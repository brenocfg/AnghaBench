#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {char* buf_end; char* nextb; } ;
typedef  TYPE_1__ buffy ;

/* Variables and functions */
 int format_converter (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void strx_printv(int *ccp, char *buf, size_t len, const char *format, va_list ap) /* {{{ */
{
	buffy od;
	int cc;

	/*
	 * First initialize the descriptor
	 * Notice that if no length is given, we initialize buf_end to the
	 * highest possible address.
	 */
	if (len == 0) {
		od.buf_end = (char *) ~0;
		od.nextb   = (char *) ~0;
	} else {
		od.buf_end = &buf[len-1];
		od.nextb   = buf;
	}

	/*
	 * Do the conversion
	 */
	cc = format_converter(&od, format, ap);
	if (len != 0 && od.nextb <= od.buf_end) {
		*(od.nextb) = '\0';
	}
	if (ccp) {
		*ccp = cc;
	}
}