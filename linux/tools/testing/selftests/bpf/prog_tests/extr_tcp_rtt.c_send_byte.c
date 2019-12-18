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
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 scalar_t__ CHECK_FAIL (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void send_byte(int fd)
{
	char b = 0x55;

	if (CHECK_FAIL(write(fd, &b, sizeof(b)) != 1))
		perror("Failed to send single byte");
}