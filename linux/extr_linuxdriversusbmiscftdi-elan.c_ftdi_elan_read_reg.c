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
struct usb_ftdi {scalar_t__ disconnected; int command_next; int command_head; int respond_next; int respond_head; int /*<<< orphan*/  u132_lock; struct u132_respond* respond; struct u132_command* command; } ;
struct u132_respond {int* result; int header; int /*<<< orphan*/  wait_completion; int /*<<< orphan*/ * value; int /*<<< orphan*/  address; } ;
struct u132_command {int header; int length; int width; int /*<<< orphan*/ * buffer; scalar_t__ value; scalar_t__ follows; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 size_t COMMAND_MASK ; 
 int COMMAND_SIZE ; 
 int ENODEV ; 
 size_t RESPOND_MASK ; 
 int RESPOND_SIZE ; 
 int cPCIu132rd ; 
 int /*<<< orphan*/  cU132cmd_status ; 
 int /*<<< orphan*/  ftdi_elan_kick_command_queue (struct usb_ftdi*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ftdi_elan_read_reg(struct usb_ftdi *ftdi, u32 *data)
{
wait:if (ftdi->disconnected > 0) {
		return -ENODEV;
	} else {
		int command_size;
		int respond_size;
		mutex_lock(&ftdi->u132_lock);
		command_size = ftdi->command_next - ftdi->command_head;
		respond_size = ftdi->respond_next - ftdi->respond_head;
		if (command_size < COMMAND_SIZE && respond_size < RESPOND_SIZE)
		{
			struct u132_command *command = &ftdi->command[
				COMMAND_MASK & ftdi->command_next];
			struct u132_respond *respond = &ftdi->respond[
				RESPOND_MASK & ftdi->respond_next];
			int result = -ENODEV;
			respond->result = &result;
			respond->header = command->header = 0x00 | cPCIu132rd;
			command->length = 0x04;
			respond->address = command->address = cU132cmd_status;
			command->width = 0x00;
			command->follows = 0;
			command->value = 0;
			command->buffer = NULL;
			respond->value = data;
			init_completion(&respond->wait_completion);
			ftdi->command_next += 1;
			ftdi->respond_next += 1;
			ftdi_elan_kick_command_queue(ftdi);
			mutex_unlock(&ftdi->u132_lock);
			wait_for_completion(&respond->wait_completion);
			return result;
		} else {
			mutex_unlock(&ftdi->u132_lock);
			msleep(100);
			goto wait;
		}
	}
}