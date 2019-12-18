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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  t ;
struct spi_transfer {int* tx_buf; int len; int* rx_buf; void* speed_hz; } ;
struct spi_message {int dummy; } ;
typedef  int /*<<< orphan*/  header ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int EACCES ; 
 int ENODEV ; 
 int RT5677_SPI_BURST_LEN ; 
 void* RT5677_SPI_FREQ ; 
 int /*<<< orphan*/  RT5677_SPI_HEADER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,size_t) ; 
 TYPE_1__* g_spi ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt5677_spi_reverse (int*,size_t,int*,int) ; 
 int rt5677_spi_select_cmd (int,int,size_t,int*) ; 
 int /*<<< orphan*/  spi_message_init_with_transfers (struct spi_message*,struct spi_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_mutex ; 
 int spi_sync (TYPE_1__*,struct spi_message*) ; 

int rt5677_spi_read(u32 addr, void *rxbuf, size_t len)
{
	u32 offset;
	int status = 0;
	struct spi_transfer t[2];
	struct spi_message m;
	/* +4 bytes is for the DummyPhase following the AddressPhase */
	u8 header[RT5677_SPI_HEADER + 4];
	u8 body[RT5677_SPI_BURST_LEN];
	u8 spi_cmd;
	u8 *cb = rxbuf;

	if (!g_spi)
		return -ENODEV;

	if ((addr & 3) || (len & 3)) {
		dev_err(&g_spi->dev, "Bad read align 0x%x(%zu)\n", addr, len);
		return -EACCES;
	}

	memset(t, 0, sizeof(t));
	t[0].tx_buf = header;
	t[0].len = sizeof(header);
	t[0].speed_hz = RT5677_SPI_FREQ;
	t[1].rx_buf = body;
	t[1].speed_hz = RT5677_SPI_FREQ;
	spi_message_init_with_transfers(&m, t, ARRAY_SIZE(t));

	for (offset = 0; offset < len; offset += t[1].len) {
		spi_cmd = rt5677_spi_select_cmd(true, (addr + offset) & 7,
				len - offset, &t[1].len);

		/* Construct SPI message header */
		header[0] = spi_cmd;
		header[1] = ((addr + offset) & 0xff000000) >> 24;
		header[2] = ((addr + offset) & 0x00ff0000) >> 16;
		header[3] = ((addr + offset) & 0x0000ff00) >> 8;
		header[4] = ((addr + offset) & 0x000000ff) >> 0;

		mutex_lock(&spi_mutex);
		status |= spi_sync(g_spi, &m);
		mutex_unlock(&spi_mutex);


		/* Copy data back to caller buffer */
		rt5677_spi_reverse(cb + offset, len - offset, body, t[1].len);
	}
	return status;
}