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
struct trace_seq {int dummy; } ;
struct tep_record {unsigned long long ts; } ;
struct tep_handle {int dummy; } ;
struct tep_event {int dummy; } ;

/* Variables and functions */
 int atoi (char*) ; 
 scalar_t__ isdigit (char) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned long long,...) ; 

__attribute__((used)) static void print_event_time(struct tep_handle *tep, struct trace_seq *s,
				 char *format, struct tep_event *event,
				 struct tep_record *record)
{
	unsigned long long time;
	char *divstr;
	int prec = 0, pr;
	int div = 0;
	int p10 = 1;

	if (isdigit(*(format + 1)))
		prec = atoi(format + 1);
	divstr = strchr(format, '.');
	if (divstr && isdigit(*(divstr + 1)))
		div = atoi(divstr + 1);
	time = record->ts;
	if (div) {
		time += div / 2;
		time /= div;
	}
	pr = prec;
	while (pr--)
		p10 *= 10;

	if (p10 > 1 && p10 < time)
		trace_seq_printf(s, "%5llu.%0*llu", time / p10, prec, time % p10);
	else
		trace_seq_printf(s, "%12llu\n", time);
}