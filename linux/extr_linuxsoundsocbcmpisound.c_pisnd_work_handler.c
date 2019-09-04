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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  txbuf ;
struct work_struct {int dummy; } ;
typedef  int /*<<< orphan*/  rxbuf ;
typedef  int /*<<< orphan*/  midibuf ;

/* Variables and functions */
 int HZ ; 
 int g_ledFlashDuration ; 
 int g_ledFlashDurationChanged ; 
 scalar_t__ g_midi_output_substream ; 
 int /*<<< orphan*/  g_recvCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_recvData ; 
 unsigned long jiffies ; 
 int kfifo_avail (int /*<<< orphan*/ *) ; 
 scalar_t__ kfifo_get (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int kfifo_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_put (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pisnd_spi_device ; 
 scalar_t__ pisnd_spi_has_more () ; 
 struct work_struct pisnd_work_process ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_ack (scalar_t__,int) ; 
 int snd_rawmidi_transmit_peek (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  spi_fifo_in ; 
 int /*<<< orphan*/  spi_fifo_out ; 
 int /*<<< orphan*/  spi_transfer (int*,int*,int) ; 

__attribute__((used)) static void pisnd_work_handler(struct work_struct *work)
{
	enum { TRANSFER_SIZE = 4 };
	enum { PISOUND_OUTPUT_BUFFER_SIZE = 128 };
	enum { MIDI_BYTES_PER_SECOND = 3125 };
	int out_buffer_used = 0;
	unsigned long now;
	uint8_t val;
	uint8_t txbuf[TRANSFER_SIZE];
	uint8_t rxbuf[TRANSFER_SIZE];
	uint8_t midibuf[TRANSFER_SIZE];
	int i, n;
	bool had_data;

	unsigned long last_transfer_at = jiffies;

	if (work == &pisnd_work_process) {
		if (pisnd_spi_device == NULL)
			return;

		do {
			if (g_midi_output_substream &&
				kfifo_avail(&spi_fifo_out) >= sizeof(midibuf)) {

				n = snd_rawmidi_transmit_peek(
					g_midi_output_substream,
					midibuf, sizeof(midibuf)
				);

				if (n > 0) {
					for (i = 0; i < n; ++i)
						kfifo_put(
							&spi_fifo_out,
							midibuf[i]
							);
					snd_rawmidi_transmit_ack(
						g_midi_output_substream,
						i
						);
				}
			}

			had_data = false;
			memset(txbuf, 0, sizeof(txbuf));
			for (i = 0; i < sizeof(txbuf) &&
				out_buffer_used < PISOUND_OUTPUT_BUFFER_SIZE;
				i += 2) {

				val = 0;

				if (g_ledFlashDurationChanged) {
					txbuf[i+0] = 0xf0;
					txbuf[i+1] = g_ledFlashDuration;
					g_ledFlashDuration = 0;
					g_ledFlashDurationChanged = false;
				} else if (kfifo_get(&spi_fifo_out, &val)) {
					txbuf[i+0] = 0x0f;
					txbuf[i+1] = val;
					++out_buffer_used;
				}
			}

			spi_transfer(txbuf, rxbuf, sizeof(txbuf));
			/* Estimate the Pisound's MIDI output buffer usage, so
			 * that we don't overflow it. Space in the buffer should
			 * be becoming available at the UART MIDI byte transfer
			 * rate.
			 */
			now = jiffies;
			out_buffer_used -=
				(MIDI_BYTES_PER_SECOND / HZ) /
				(now - last_transfer_at);
			if (out_buffer_used < 0)
				out_buffer_used = 0;
			last_transfer_at = now;

			for (i = 0; i < sizeof(rxbuf); i += 2) {
				if (rxbuf[i]) {
					kfifo_put(&spi_fifo_in, rxbuf[i+1]);
					if (kfifo_len(&spi_fifo_in) > 16 &&
						g_recvCallback)
						g_recvCallback(g_recvData);
					had_data = true;
				}
			}
		} while (had_data
			|| !kfifo_is_empty(&spi_fifo_out)
			|| pisnd_spi_has_more()
			|| g_ledFlashDurationChanged
			);

		if (!kfifo_is_empty(&spi_fifo_in) && g_recvCallback)
			g_recvCallback(g_recvData);
	}
}