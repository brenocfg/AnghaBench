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
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void usage(const char *filepath)
{
	error(1, 0, "Usage: %s [-C connect_timeout] [-Grtv] [-b addr] [-p port]"
	      " [-l pktlen] [-n packetnr] [-R rcv_timeout] [-S gsosize]",
	      filepath);
}