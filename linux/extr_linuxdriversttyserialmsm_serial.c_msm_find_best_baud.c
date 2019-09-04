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
struct uart_port {int dummy; } ;
struct msm_port {int /*<<< orphan*/  clk; } ;
struct msm_baud_map {int member_0; int member_1; int member_2; unsigned int divisor; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct msm_baud_map const*) ; 
 unsigned int DIV_ROUND_CLOSEST (unsigned long,int) ; 
 struct msm_port* UART_TO_MSM (struct uart_port*) ; 
 unsigned long ULONG_MAX ; 
 unsigned long abs (unsigned int) ; 
 unsigned long clk_round_rate (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static const struct msm_baud_map *
msm_find_best_baud(struct uart_port *port, unsigned int baud,
		   unsigned long *rate)
{
	struct msm_port *msm_port = UART_TO_MSM(port);
	unsigned int divisor, result;
	unsigned long target, old, best_rate = 0, diff, best_diff = ULONG_MAX;
	const struct msm_baud_map *entry, *end, *best;
	static const struct msm_baud_map table[] = {
		{    1, 0xff, 31 },
		{    2, 0xee, 16 },
		{    3, 0xdd,  8 },
		{    4, 0xcc,  6 },
		{    6, 0xbb,  6 },
		{    8, 0xaa,  6 },
		{   12, 0x99,  6 },
		{   16, 0x88,  1 },
		{   24, 0x77,  1 },
		{   32, 0x66,  1 },
		{   48, 0x55,  1 },
		{   96, 0x44,  1 },
		{  192, 0x33,  1 },
		{  384, 0x22,  1 },
		{  768, 0x11,  1 },
		{ 1536, 0x00,  1 },
	};

	best = table; /* Default to smallest divider */
	target = clk_round_rate(msm_port->clk, 16 * baud);
	divisor = DIV_ROUND_CLOSEST(target, 16 * baud);

	end = table + ARRAY_SIZE(table);
	entry = table;
	while (entry < end) {
		if (entry->divisor <= divisor) {
			result = target / entry->divisor / 16;
			diff = abs(result - baud);

			/* Keep track of best entry */
			if (diff < best_diff) {
				best_diff = diff;
				best = entry;
				best_rate = target;
			}

			if (result == baud)
				break;
		} else if (entry->divisor > divisor) {
			old = target;
			target = clk_round_rate(msm_port->clk, old + 1);
			/*
			 * The rate didn't get any faster so we can't do
			 * better at dividing it down
			 */
			if (target == old)
				break;

			/* Start the divisor search over at this new rate */
			entry = table;
			divisor = DIV_ROUND_CLOSEST(target, 16 * baud);
			continue;
		}
		entry++;
	}

	*rate = best_rate;
	return best;
}