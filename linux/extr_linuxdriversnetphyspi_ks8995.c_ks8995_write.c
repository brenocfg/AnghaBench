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
typedef  int /*<<< orphan*/  t ;
struct spi_transfer {char* tx_buf; int len; } ;
struct spi_message {int dummy; } ;
struct ks8995_switch {int /*<<< orphan*/  lock; int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  char __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  KS8995_CMD_WRITE ; 
 char create_spi_cmd (struct ks8995_switch*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int ks8995_write(struct ks8995_switch *ks, char *buf,
		 unsigned offset, size_t count)
{
	__be16 cmd;
	struct spi_transfer t[2];
	struct spi_message m;
	int err;

	cmd = create_spi_cmd(ks, KS8995_CMD_WRITE, offset);
	spi_message_init(&m);

	memset(&t, 0, sizeof(t));

	t[0].tx_buf = &cmd;
	t[0].len = sizeof(cmd);
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].len = count;
	spi_message_add_tail(&t[1], &m);

	mutex_lock(&ks->lock);
	err = spi_sync(ks->spi, &m);
	mutex_unlock(&ks->lock);

	return err ? err : count;
}