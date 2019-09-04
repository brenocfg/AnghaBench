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
struct spi_ioc_transfer {unsigned long tx_buf; unsigned long rx_buf; size_t len; int tx_nbits; int rx_nbits; int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/  speed_hz; int /*<<< orphan*/  delay_usecs; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SPI_IOC_MESSAGE (int) ; 
 int SPI_LOOP ; 
 int SPI_RX_DUAL ; 
 int SPI_RX_QUAD ; 
 int SPI_TX_DUAL ; 
 int SPI_TX_QUAD ; 
 int /*<<< orphan*/  bits ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  delay ; 
 int /*<<< orphan*/  hex_dump (int /*<<< orphan*/  const*,size_t,int,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct spi_ioc_transfer*) ; 
 int mode ; 
 int open (scalar_t__,int,int) ; 
 scalar_t__ output_file ; 
 int /*<<< orphan*/  pabort (char*) ; 
 int /*<<< orphan*/  speed ; 
 scalar_t__ verbose ; 
 int write (int,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void transfer(int fd, uint8_t const *tx, uint8_t const *rx, size_t len)
{
	int ret;
	int out_fd;
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = len,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	if (mode & SPI_TX_QUAD)
		tr.tx_nbits = 4;
	else if (mode & SPI_TX_DUAL)
		tr.tx_nbits = 2;
	if (mode & SPI_RX_QUAD)
		tr.rx_nbits = 4;
	else if (mode & SPI_RX_DUAL)
		tr.rx_nbits = 2;
	if (!(mode & SPI_LOOP)) {
		if (mode & (SPI_TX_QUAD | SPI_TX_DUAL))
			tr.rx_buf = 0;
		else if (mode & (SPI_RX_QUAD | SPI_RX_DUAL))
			tr.tx_buf = 0;
	}

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
		pabort("can't send spi message");

	if (verbose)
		hex_dump(tx, len, 32, "TX");

	if (output_file) {
		out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (out_fd < 0)
			pabort("could not open output file");

		ret = write(out_fd, rx, len);
		if (ret != len)
			pabort("not all bytes written to output file");

		close(out_fd);
	}

	if (verbose)
		hex_dump(rx, len, 32, "RX");
}