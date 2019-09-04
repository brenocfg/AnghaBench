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
typedef  int uint32_t ;
struct spi_transfer {int len; } ;
struct tdo24m {int* buf; int /*<<< orphan*/  msg; int /*<<< orphan*/  spi_dev; int /*<<< orphan*/  color_invert; struct spi_transfer xfer; } ;

/* Variables and functions */
 int const CMD0 (int) ; 
 int const CMD_NULL ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tdo24m_writes(struct tdo24m *lcd, const uint32_t *array)
{
	struct spi_transfer *x = &lcd->xfer;
	const uint32_t *p = array;
	uint32_t data;
	int nparams, err = 0;

	for (; *p != CMD_NULL; p++) {
		if (!lcd->color_invert && *p == CMD0(0x21))
			continue;

		nparams = (*p >> 30) & 0x3;

		data = *p << (7 - nparams);
		switch (nparams) {
		case 0:
			lcd->buf[0] = (data >> 8) & 0xff;
			lcd->buf[1] = data & 0xff;
			break;
		case 1:
			lcd->buf[0] = (data >> 16) & 0xff;
			lcd->buf[1] = (data >> 8) & 0xff;
			lcd->buf[2] = data & 0xff;
			break;
		case 2:
			lcd->buf[0] = (data >> 24) & 0xff;
			lcd->buf[1] = (data >> 16) & 0xff;
			lcd->buf[2] = (data >> 8) & 0xff;
			lcd->buf[3] = data & 0xff;
			break;
		default:
			continue;
		}
		x->len = nparams + 2;
		err = spi_sync(lcd->spi_dev, &lcd->msg);
		if (err)
			break;
	}

	return err;
}