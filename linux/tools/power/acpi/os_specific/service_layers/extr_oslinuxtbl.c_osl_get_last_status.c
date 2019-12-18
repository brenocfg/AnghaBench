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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AE_ACCESS ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
#define  EACCES 131 
#define  ENOENT 130 
#define  ENOMEM 129 
#define  EPERM 128 
 int errno ; 

__attribute__((used)) static acpi_status osl_get_last_status(acpi_status default_status)
{

	switch (errno) {
	case EACCES:
	case EPERM:

		return (AE_ACCESS);

	case ENOENT:

		return (AE_NOT_FOUND);

	case ENOMEM:

		return (AE_NO_MEMORY);

	default:

		return (default_status);
	}
}