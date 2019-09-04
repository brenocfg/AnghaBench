#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct mbo {int /*<<< orphan*/  (* complete ) (struct mbo*) ;int /*<<< orphan*/  status; int /*<<< orphan*/  processed_length; int /*<<< orphan*/  virt_address; int /*<<< orphan*/  buffer_length; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct hdm_i2c {TYPE_1__ rx; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int MAX_BUF_SIZE_CONTROL ; 
 int /*<<< orphan*/  MBO_SUCCESS ; 
 int i2c_master_recv (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct mbo* list_first_mbo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (struct mbo*) ; 

__attribute__((used)) static void do_rx_work(struct hdm_i2c *dev)
{
	struct mbo *mbo;
	unsigned char msg[MAX_BUF_SIZE_CONTROL];
	int ret;
	u16 pml, data_size;

	/* Read PML (2 bytes) */
	ret = i2c_master_recv(dev->client, msg, 2);
	if (ret <= 0) {
		pr_err("Failed to receive PML\n");
		return;
	}

	pml = (msg[0] << 8) | msg[1];
	if (!pml)
		return;

	data_size = pml + 2;

	/* Read the whole message, including PML */
	ret = i2c_master_recv(dev->client, msg, data_size);
	if (ret <= 0) {
		pr_err("Failed to receive a Port Message\n");
		return;
	}

	mbo = list_first_mbo(&dev->rx.list);
	list_del(&mbo->list);

	mbo->processed_length = min(data_size, mbo->buffer_length);
	memcpy(mbo->virt_address, msg, mbo->processed_length);
	mbo->status = MBO_SUCCESS;
	mbo->complete(mbo);
}