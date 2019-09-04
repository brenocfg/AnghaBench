#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* spidev; } ;
struct st95hf_context {TYPE_2__ spicontext; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int st95hf_echo_command (struct st95hf_context*) ; 
 int /*<<< orphan*/  st95hf_send_spi_reset_sequence (struct st95hf_context*) ; 
 int /*<<< orphan*/  st95hf_send_st95enable_negativepulse (struct st95hf_context*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int st95hf_por_sequence(struct st95hf_context *st95context)
{
	int nth_attempt = 1;
	int result;

	st95hf_send_st95enable_negativepulse(st95context);

	usleep_range(5000, 6000);
	do {
		/* send an ECHO command and checks ST95HF response */
		result = st95hf_echo_command(st95context);

		dev_dbg(&st95context->spicontext.spidev->dev,
			"response from echo function = 0x%x, attempt = %d\n",
			result, nth_attempt);

		if (!result)
			return 0;

		/* send an pulse on IRQ in case of the chip is on sleep state */
		if (nth_attempt == 2)
			st95hf_send_st95enable_negativepulse(st95context);
		else
			st95hf_send_spi_reset_sequence(st95context);

		/* delay of 50 milisecond */
		usleep_range(50000, 51000);
	} while (nth_attempt++ < 3);

	return -ETIMEDOUT;
}