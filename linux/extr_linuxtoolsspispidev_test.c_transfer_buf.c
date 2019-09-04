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

/* Variables and functions */
 int SPI_LOOP ; 
 int _read_count ; 
 int _write_count ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hex_dump (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mode ; 
 int /*<<< orphan*/  pabort (char*) ; 
 int /*<<< orphan*/  random () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  transfer (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void transfer_buf(int fd, int len)
{
	uint8_t *tx;
	uint8_t *rx;
	int i;

	tx = malloc(len);
	if (!tx)
		pabort("can't allocate tx buffer");
	for (i = 0; i < len; i++)
		tx[i] = random();

	rx = malloc(len);
	if (!rx)
		pabort("can't allocate rx buffer");

	transfer(fd, tx, rx, len);

	_write_count += len;
	_read_count += len;

	if (mode & SPI_LOOP) {
		if (memcmp(tx, rx, len)) {
			fprintf(stderr, "transfer error !\n");
			hex_dump(tx, len, 32, "TX");
			hex_dump(rx, len, 32, "RX");
			exit(1);
		}
	}

	free(rx);
	free(tx);
}