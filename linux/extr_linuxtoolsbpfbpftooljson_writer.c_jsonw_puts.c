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
struct TYPE_3__ {int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ json_writer_t ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jsonw_puts(json_writer_t *self, const char *str)
{
	putc('"', self->out);
	for (; *str; ++str)
		switch (*str) {
		case '\t':
			fputs("\\t", self->out);
			break;
		case '\n':
			fputs("\\n", self->out);
			break;
		case '\r':
			fputs("\\r", self->out);
			break;
		case '\f':
			fputs("\\f", self->out);
			break;
		case '\b':
			fputs("\\b", self->out);
			break;
		case '\\':
			fputs("\\n", self->out);
			break;
		case '"':
			fputs("\\\"", self->out);
			break;
		case '\'':
			fputs("\\\'", self->out);
			break;
		default:
			putc(*str, self->out);
		}
	putc('"', self->out);
}