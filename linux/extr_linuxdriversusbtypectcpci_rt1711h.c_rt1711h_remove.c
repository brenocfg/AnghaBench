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
struct rt1711h_chip {int /*<<< orphan*/  tcpci; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct rt1711h_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  tcpci_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt1711h_remove(struct i2c_client *client)
{
	struct rt1711h_chip *chip = i2c_get_clientdata(client);

	tcpci_unregister_port(chip->tcpci);
	return 0;
}