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
struct nci_dev {int dummy; } ;
struct nci_data {int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  nci_hci_send_data (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nci_hci_send_data_req(struct nci_dev *ndev, unsigned long opt)
{
	struct nci_data *data = (struct nci_data *)opt;

	nci_hci_send_data(ndev, data->pipe, data->cmd,
			  data->data, data->data_len);
}