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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  t ;
struct wl12xx_spi_glue {int /*<<< orphan*/  dev; } ;
struct spi_transfer {int* tx_buf; int len; } ;
struct spi_message {int* tx_buf; int len; } ;
struct spi_device {int /*<<< orphan*/  mode; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  m ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HW_ACCESS_WSPI_FIXED_BUSY_LEN ; 
 int HW_ACCESS_WSPI_INIT_CMD_MASK ; 
 int /*<<< orphan*/  SPI_CS_HIGH ; 
 int /*<<< orphan*/  WSPI_INIT_CMD_CRC_LEN ; 
 int WSPI_INIT_CMD_CS ; 
 int WSPI_INIT_CMD_DIS_FIXEDBUSY ; 
 int WSPI_INIT_CMD_END ; 
 int WSPI_INIT_CMD_EN_FIXEDBUSY ; 
 int WSPI_INIT_CMD_FIXEDBUSY_LEN ; 
 int WSPI_INIT_CMD_IOD ; 
 int WSPI_INIT_CMD_IP ; 
 int WSPI_INIT_CMD_LEN ; 
 int WSPI_INIT_CMD_START ; 
 int WSPI_INIT_CMD_TX ; 
 int WSPI_INIT_CMD_WS ; 
 int WSPI_INIT_CMD_WSPI ; 
 int /*<<< orphan*/  __swab32s (int /*<<< orphan*/ *) ; 
 int crc7_be (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct wl12xx_spi_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_transfer*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_transfer*) ; 
 int /*<<< orphan*/  spi_sync (struct spi_device*,struct spi_transfer*) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl12xx_spi_init(struct device *child)
{
	struct wl12xx_spi_glue *glue = dev_get_drvdata(child->parent);
	struct spi_transfer t;
	struct spi_message m;
	struct spi_device *spi = to_spi_device(glue->dev);
	u8 *cmd = kzalloc(WSPI_INIT_CMD_LEN, GFP_KERNEL);

	if (!cmd) {
		dev_err(child->parent,
			"could not allocate cmd for spi init\n");
		return;
	}

	memset(&t, 0, sizeof(t));
	spi_message_init(&m);

	/*
	 * Set WSPI_INIT_COMMAND
	 * the data is being send from the MSB to LSB
	 */
	cmd[0] = 0xff;
	cmd[1] = 0xff;
	cmd[2] = WSPI_INIT_CMD_START | WSPI_INIT_CMD_TX;
	cmd[3] = 0;
	cmd[4] = 0;
	cmd[5] = HW_ACCESS_WSPI_INIT_CMD_MASK << 3;
	cmd[5] |= HW_ACCESS_WSPI_FIXED_BUSY_LEN & WSPI_INIT_CMD_FIXEDBUSY_LEN;

	cmd[6] = WSPI_INIT_CMD_IOD | WSPI_INIT_CMD_IP | WSPI_INIT_CMD_CS
		| WSPI_INIT_CMD_WSPI | WSPI_INIT_CMD_WS;

	if (HW_ACCESS_WSPI_FIXED_BUSY_LEN == 0)
		cmd[6] |= WSPI_INIT_CMD_DIS_FIXEDBUSY;
	else
		cmd[6] |= WSPI_INIT_CMD_EN_FIXEDBUSY;

	cmd[7] = crc7_be(0, cmd+2, WSPI_INIT_CMD_CRC_LEN) | WSPI_INIT_CMD_END;

	/*
	 * The above is the logical order; it must actually be stored
	 * in the buffer byte-swapped.
	 */
	__swab32s((u32 *)cmd);
	__swab32s((u32 *)cmd+1);

	t.tx_buf = cmd;
	t.len = WSPI_INIT_CMD_LEN;
	spi_message_add_tail(&t, &m);

	spi_sync(to_spi_device(glue->dev), &m);

	/* Send extra clocks with inverted CS (high). this is required
	 * by the wilink family in order to successfully enter WSPI mode.
	 */
	spi->mode ^= SPI_CS_HIGH;
	memset(&m, 0, sizeof(m));
	spi_message_init(&m);

	cmd[0] = 0xff;
	cmd[1] = 0xff;
	cmd[2] = 0xff;
	cmd[3] = 0xff;
	__swab32s((u32 *)cmd);

	t.tx_buf = cmd;
	t.len = 4;
	spi_message_add_tail(&t, &m);

	spi_sync(to_spi_device(glue->dev), &m);

	/* Restore chip select configration to normal */
	spi->mode ^= SPI_CS_HIGH;
	kfree(cmd);
}