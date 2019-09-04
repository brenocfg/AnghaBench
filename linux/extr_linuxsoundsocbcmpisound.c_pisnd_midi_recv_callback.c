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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  pisnd_spi_recv (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printd (char*,int /*<<< orphan*/ ,int) ; 
 int snd_rawmidi_receive (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pisnd_midi_recv_callback(void *substream)
{
	uint8_t data[128];
	uint8_t n = 0;

	while ((n = pisnd_spi_recv(data, sizeof(data)))) {
		int res = snd_rawmidi_receive(substream, data, n);
		(void)res;
		printd("midi recv %u bytes, res = %d\n", n, res);
	}
}