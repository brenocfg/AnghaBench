#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct oxygen {int uart_input_count; char* uart_input; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,char*,int) ; 

void xonar_hdmi_uart_input(struct oxygen *chip)
{
	if (chip->uart_input_count >= 2 &&
	    chip->uart_input[chip->uart_input_count - 2] == 'O' &&
	    chip->uart_input[chip->uart_input_count - 1] == 'K') {
		dev_dbg(chip->card->dev, "message from HDMI chip received:\n");
		print_hex_dump_bytes("", DUMP_PREFIX_OFFSET,
				     chip->uart_input, chip->uart_input_count);
		chip->uart_input_count = 0;
	}
}