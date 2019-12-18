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
struct timeval {int /*<<< orphan*/  tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_AML_USEC_PEEK ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int acpi_aml_set_fd (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static bool acpi_aml_readable(int fd)
{
	fd_set rfds;
	struct timeval tv;
	int ret;
	int maxfd = 0;

	tv.tv_sec = 0;
	tv.tv_usec = ACPI_AML_USEC_PEEK;
	FD_ZERO(&rfds);
	maxfd = acpi_aml_set_fd(fd, maxfd, &rfds);
	ret = select(maxfd+1, &rfds, NULL, NULL, &tv);
	if (ret < 0)
		perror("select");
	if (ret > 0 && FD_ISSET(fd, &rfds))
		return true;
	return false;
}