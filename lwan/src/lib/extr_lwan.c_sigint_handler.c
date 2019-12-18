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
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int main_socket ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sigint_handler(int signal_number __attribute__((unused)))
{
    if (main_socket < 0)
        return;

    shutdown((int)main_socket, SHUT_RDWR);
    close((int)main_socket);

    main_socket = -1;
}