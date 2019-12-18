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
struct spi_transfer {int* tx_buf; int len; int /*<<< orphan*/  speed_hz; } ;
struct spi_message {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EACCES ; 
 int ENODEV ; 
 int RT5677_SPI_BURST_LEN ; 
 int /*<<< orphan*/  RT5677_SPI_FREQ ; 
 int RT5677_SPI_HEADER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,size_t) ; 
 TYPE_1__* g_spi ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt5677_spi_reverse (int*,int,int const*,size_t) ; 
 int rt5677_spi_select_cmd (int,int,size_t,int*) ; 
 int /*<<< orphan*/  spi_message_init_with_transfers (struct spi_message*,struct spi_transfer*,int) ; 
 int /*<<< orphan*/  spi_mutex ; 
 int spi_sync (TYPE_1__*,struct spi_message*) ; 

int rt5677_spi_write(u32 addr, const void *txbuf, size_t len)
{
	u32 offset;
	int status = 0;
	struct spi_transfer t;
	struct spi_message m;
	/* +1 byte is for the DummyPhase following the DataPhase */
	u8 buf[RT5677_SPI_HEADER + RT5677_SPI_BURST_LEN + 1];
	u8 *body = buf + RT5677_SPI_HEADER;
	u8 spi_cmd;
	const u8 *cb = txbuf;

	if (!g_spi)
		return -ENODEV;

	if (addr & 3) {
		dev_err(&g_spi->dev, "Bad write align 0x%x(%zu)\n", addr, len);
		return -EACCES;
	}

	memset(&t, 0, sizeof(t));
	t.tx_buf = buf;
	t.speed_hz = RT5677_SPI_FREQ;
	spi_message_init_with_transfers(&m, &t, 1);

	for (offset = 0; offset < len;) {
		spi_cmd = rt5677_spi_select_cmd(false, (addr + offset) & 7,
				len - offset, &t.len);

		/* Construct SPI message header */
		buf[0] = spi_cmd;
		buf[1] = ((addr + offset) & 0xff000000) >> 24;
		buf[2] = ((addr + offset) & 0x00ff0000) >> 16;
		buf[3] = ((addr + offset) & 0x0000ff00) >> 8;
		buf[4] = ((addr + offset) & 0x000000ff) >> 0;

		/* Fetch data from caller buffer */
		rt5677_spi_reverse(body, t.len, cb + offset, len - offset);
		offset += t.len;
		t.len += RT5677_SPI_HEADER + 1;

		mutex_lock(&spi_mutex);
		status |= spi_sync(g_spi, &m);
		mutex_unlock(&spi_mutex);
	}
	return status;
}