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
typedef  scalar_t__ u8 ;
struct spi_transfer {int dummy; } ;
struct spi_message {int dummy; } ;
struct spi_device {int dummy; } ;
struct ds1305 {struct spi_device* spi; } ;

/* Variables and functions */
 scalar_t__ DS1305_NVRAM ; 
 int /*<<< orphan*/  msg_init (struct spi_message*,struct spi_transfer*,scalar_t__*,size_t,int /*<<< orphan*/ *,void*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 

__attribute__((used)) static int ds1305_nvram_read(void *priv, unsigned int off, void *buf,
			     size_t count)
{
	struct ds1305		*ds1305 = priv;
	struct spi_device	*spi = ds1305->spi;
	u8			addr;
	struct spi_message	m;
	struct spi_transfer	x[2];

	addr = DS1305_NVRAM + off;
	msg_init(&m, x, &addr, count, NULL, buf);

	return spi_sync(spi, &m);
}