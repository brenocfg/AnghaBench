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

/* Variables and functions */
 int card_send_command (int const*,char const*,unsigned char const*,unsigned char*) ; 
 int sb1000_end_get_set_command (int const*,char const*) ; 
 int sb1000_start_get_set_command (int const*,char const*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
sb1000_set_PIDs(const int ioaddr[], const char* name, const short PID[])
{
	static const unsigned char Command4[6] = {0x80, 0x2e, 0x00, 0x00, 0x00, 0x00};

	unsigned char st[7];
	short p;
	int status;
	unsigned char Command0[6] = {0x80, 0x31, 0x00, 0x00, 0x00, 0x00};
	unsigned char Command1[6] = {0x80, 0x32, 0x00, 0x00, 0x00, 0x00};
	unsigned char Command2[6] = {0x80, 0x33, 0x00, 0x00, 0x00, 0x00};
	unsigned char Command3[6] = {0x80, 0x34, 0x00, 0x00, 0x00, 0x00};

	udelay(1000);
	if ((status = sb1000_start_get_set_command(ioaddr, name)))
		return status;

	p = PID[0];
	Command0[3] = p & 0xff;
	p >>= 8;
	Command0[2] = p & 0xff;
	if ((status = card_send_command(ioaddr, name, Command0, st)))
		return status;

	p = PID[1];
	Command1[3] = p & 0xff;
	p >>= 8;
	Command1[2] = p & 0xff;
	if ((status = card_send_command(ioaddr, name, Command1, st)))
		return status;

	p = PID[2];
	Command2[3] = p & 0xff;
	p >>= 8;
	Command2[2] = p & 0xff;
	if ((status = card_send_command(ioaddr, name, Command2, st)))
		return status;

	p = PID[3];
	Command3[3] = p & 0xff;
	p >>= 8;
	Command3[2] = p & 0xff;
	if ((status = card_send_command(ioaddr, name, Command3, st)))
		return status;

	if ((status = card_send_command(ioaddr, name, Command4, st)))
		return status;
	return sb1000_end_get_set_command(ioaddr, name);
}