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
typedef  int /*<<< orphan*/  u32 ;
struct dsi_packet_sent_handler_data {int /*<<< orphan*/  completion; int /*<<< orphan*/  dsidev; } ;
struct dsi_data {int update_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int const) ; 
 scalar_t__ REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 struct dsi_data* dsi_get_dsidrv_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_packet_sent_handler_l4(void *data, u32 mask)
{
	struct dsi_packet_sent_handler_data *l4_data =
		(struct dsi_packet_sent_handler_data *) data;
	struct dsi_data *dsi = dsi_get_dsidrv_data(l4_data->dsidev);
	const int channel = dsi->update_channel;

	if (REG_GET(l4_data->dsidev, DSI_VC_CTRL(channel), 5, 5) == 0)
		complete(l4_data->completion);
}