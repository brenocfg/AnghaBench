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
struct wl1251 {int dummy; } ;
struct spi_transfer {int* tx_buf; int /*<<< orphan*/  len; } ;
struct spi_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SPI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HW_ACCESS_WSPI_FIXED_BUSY_LEN ; 
 int HW_ACCESS_WSPI_INIT_CMD_MASK ; 
 int /*<<< orphan*/  WSPI_INIT_CMD_CRC_LEN ; 
 int WSPI_INIT_CMD_CS ; 
 int WSPI_INIT_CMD_DIS_FIXEDBUSY ; 
 int WSPI_INIT_CMD_END ; 
 int WSPI_INIT_CMD_EN_FIXEDBUSY ; 
 int WSPI_INIT_CMD_FIXEDBUSY_LEN ; 
 int WSPI_INIT_CMD_IOD ; 
 int WSPI_INIT_CMD_IP ; 
 int /*<<< orphan*/  WSPI_INIT_CMD_LEN ; 
 int WSPI_INIT_CMD_START ; 
 int WSPI_INIT_CMD_TX ; 
 int WSPI_INIT_CMD_WS ; 
 int WSPI_INIT_CMD_WSPI ; 
 int /*<<< orphan*/  __swab32s (int /*<<< orphan*/ *) ; 
 int crc7_be (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int /*<<< orphan*/  spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 int /*<<< orphan*/  wl1251_dump (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_error (char*) ; 
 int /*<<< orphan*/  wl_to_spi (struct wl1251*) ; 

__attribute__((used)) static void wl1251_spi_wake(struct wl1251 *wl)
{
	struct spi_transfer t;
	struct spi_message m;
	u8 *cmd = kzalloc(WSPI_INIT_CMD_LEN, GFP_KERNEL);

	if (!cmd) {
		wl1251_error("could not allocate cmd for spi init");
		return;
	}

	memset(&t, 0, sizeof(t));
	spi_message_init(&m);

	/* Set WSPI_INIT_COMMAND
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

	spi_sync(wl_to_spi(wl), &m);

	wl1251_dump(DEBUG_SPI, "spi init -> ", cmd, WSPI_INIT_CMD_LEN);

	kfree(cmd);
}